import nltk
from nltk.corpus import wordnet
from nltk.stem import WordNetLemmatizer
from nltk.tokenize import word_tokenize
from nltk import pos_tag
import random

# --- Download NLTK data (ensure this runs only once) ---
nltk.download('punkt')
nltk.download('wordnet')
nltk.download('averaged_perceptron_tagger')
nltk.download('stopwords')

# --- NLP Setup ---
lemmatizer = WordNetLemmatizer()

def get_wordnet_pos(treebank_tag):
    if treebank_tag.startswith('J'):
        return wordnet.ADJ
    elif treebank_tag.startswith('V'):
        return wordnet.VERB
    elif treebank_tag.startswith('N'):
        return wordnet.NOUN
    elif treebank_tag.startswith('R'):
        return wordnet.ADV
    else:
        return wordnet.NOUN

def preprocess_text(text):
    text = text.lower()
    tokens = word_tokenize(text)
    tagged_tokens = pos_tag(tokens)
    return [lemmatizer.lemmatize(word=word, pos=get_wordnet_pos(tag)) for word, tag in tagged_tokens]

# --- Grocery Store Inventory ---
grocery_items = {
    "Fruits": {
        "Apples": "₹120/kg",
        "Bananas": "₹60/dozen",
        "Oranges": "₹80/kg",
        "Grapes": "₹150/kg",
        "Watermelon": "₹50/piece"
    },
    "Vegetables": {
        "Tomatoes": "₹40/kg",
        "Potatoes": "₹30/kg",
        "Onions": "₹25/kg",
        "Carrots": "₹60/kg",
        "Spinach": "₹30/bunch"
    },
    "Dairy": {
        "Milk": "₹60/liter",
        "Cheese": "₹120/pack",
        "Yogurt": "₹40/cup",
        "Butter": "₹50/100g",
        "Eggs": "₹80/dozen"
    },
    "Bakery": {
        "Bread": "₹40/loaf",
        "Buns": "₹30/pack",
        "Cake": "₹200/piece",
        "Cookies": "₹80/pack",
        "Muffins": "₹25/piece"
    },
    "Pantry": {
        "Rice": "₹70/kg",
        "Flour": "₹45/kg",
        "Sugar": "₹50/kg",
        "Salt": "₹20/pack",
        "Oil": "₹120/liter"
    }
}

# Shopping cart to store items
shopping_cart = {}

# --- Response Rules ---
rules = {
    ('hello', 'hi', 'hey', 'greeting', 'wassup'):
        ["Hello there! Welcome to our grocery store. How can I help you today?", 
         "Hi! What groceries are you looking for today?", 
         "Hey! Good to see you. Need help finding anything?"],
    
    ('thank', 'thanks', 'appreciate'):
        ["You're welcome!", "No problem! Happy shopping.", "Glad to help!"],
    
    ('bye', 'goodbye', 'exit', 'quit', 'see you'):
        ["Goodbye! Hope to see you again soon.", 
         "Farewell! Have a wonderful day.", 
         "Bye! Come back anytime."],
    
    ( 'inventory', 'what', 'have', 'offer', 'items', 'products', 'grocery', 'groceries'):
        ["Here's what we offer:\n\n" + "\n\n".join(
            [f"**{category}**\n" + "\n".join([f"- {item}: {price}" for item, price in items.items()])
             for category, items in grocery_items.items()])],
    
    ('fruit', 'fruits', 'apple', 'banana', 'orange', 'grape', 'watermelon'):
        ["Here are our fruits:\n" + "\n".join([f"- {item}: {price}" for item, price in grocery_items["Fruits"].items()])],
    
    ('vegetable', 'vegetables', 'tomato', 'potato', 'onion', 'carrot', 'spinach'):
        ["Here are our vegetables:\n" + "\n".join([f"- {item}: {price}" for item, price in grocery_items["Vegetables"].items()])],
    
    ('dairy', 'milk', 'cheese', 'yogurt', 'butter', 'egg'):
        ["Here are our dairy products:\n" + "\n".join([f"- {item}: {price}" for item, price in grocery_items["Dairy"].items()])],
    
    ('bakery', 'bread', 'bun', 'cake', 'cookie', 'muffin'):
        ["Here are our bakery items:\n" + "\n".join([f"- {item}: {price}" for item, price in grocery_items["Bakery"].items()])],
    
    ('pantry', 'rice', 'flour', 'sugar', 'salt', 'oil'):
        ["Here are our pantry items:\n" + "\n".join([f"- {item}: {price}" for item, price in grocery_items["Pantry"].items()])],
    
    ('pay', 'payment', 'card', 'cash', 'credit', 'upi'):
        ["We accept cash, card, and UPI payments (GPay, PhonePe, Paytm)."],
    
    ('deliver', 'delivery', 'shipping', 'ship'):
        ["We offer free delivery for orders above ₹500. Deliveries typically arrive within 2-3 hours."],
    
    ('hour', 'time', 'open', 'close'):
        ["Our store is open from 8:00 AM to 10:00 PM daily."],
    
    ('location', 'address', 'where', 'find'):
        ["Our address: 25 Market Street, Koramangala, Bangalore."],
    
    ('fresh', 'quality', 'organic'):
        ["We pride ourselves on offering fresh, high-quality produce. Many of our fruits and vegetables are locally sourced and organic."],
    
    ('help', 'assist', 'support', 'question'):
        ["I can help you with our inventory, prices, adding items to your cart, placing orders, and more!"]
}

# --- Chatbot Logic ---

def match_rule(user_input):
    preprocessed = preprocess_text(user_input)
    matched_responses = []
    best_score=0
    ans = "Thanks"
    for keywords, responses in rules.items():
        score=0
        for word in keywords:
            if word in preprocessed:
                score+=1
            # matched_responses.extend(responses)
        if best_score<score:
            ans=responses[0]
    return ans if ans else None
    # return matched_responses if matched_responses else None

def add_to_cart(item_name):
    for category, items in grocery_items.items():
        for item, price in items.items():
            if item_name.lower() in item.lower():
                if item in shopping_cart:
                    shopping_cart[item]["quantity"] += 1
                else:
                    shopping_cart[item] = {"price": price, "quantity": 1}
                return f"{item} has been added to your cart."
    return f"Sorry, we couldn't find '{item_name}' in our inventory."

def view_cart():
    if not shopping_cart:
        return "Your cart is currently empty."
    result = "Your Shopping Cart:\n"
    for item, info in shopping_cart.items():
        result += f"- {item} ({info['quantity']}x) @ {info['price']}\n"
    return result

# --- Main Chat Loop ---
def run_chatbot():
    print("🛒 Welcome to the Grocery Store Chatbot!")
    print("Type 'exit' to end the conversation.")
    while True:
        user_input = input("\nYou: ")
        if user_input.lower() in ['exit', 'quit', 'bye']:
            print("Bot:", random.choice(rules[('bye', 'goodbye', 'exit', 'quit', 'see you')]))
            break
        elif 'add' in user_input.lower():
            words = preprocess_text(user_input)
            for word in words:
                response = add_to_cart(word)
                if "added" in response:
                    print("Bot:", response)
                    break
            else:
                print("Bot: Sorry, I couldn't understand which item to add.")
        elif 'cart' in user_input.lower() or 'show' in user_input.lower():
            print("Bot:", view_cart())
        else:
            response = match_rule(user_input)
            if response:
                print("Bot:", response)
            else:
                print("Bot: I'm not sure how to respond to that. Could you please rephrase?")

# --- Run the chatbot ---
import streamlit as st
st.session_state.chat_history = []

if __name__ == "__main__":
    # for keywords, responses in rules.items():
    #     print(keywords)
    inp = st.text_input("you: ",key = "inp")
    if st.button("send"):
        response = match_rule(inp)
        st.write(response)
        
    # run_chatbot()

# 9665698566
