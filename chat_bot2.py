import nltk
from nltk.corpus import wordnet
from nltk.stem import WordNetLemmatizer
from nltk.tokenize import word_tokenize
from nltk import pos_tag
import random
import streamlit as st

# --- Download NLTK data (ensure this runs only once) ---
import nltk
nltk.download('punkt')
nltk.download('wordnet')
nltk.download('omw-1.4')
nltk.download('stopwords')
# import nltk
nltk.download('averaged_perceptron_tagger_eng')
 

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

# --- Cafe Menu with Prices ---
menu = {
    "Coffee": {
        "Espresso": "₹100",
        "Americano": "₹120",
        "Latte": "₹150",
        "Cappuccino": "₹150",
        "Mocha": "₹160",
        "Flat White": "₹160"
    },
    "Tea": {
        "Black Tea": "₹90",
        "Green Tea": "₹100",
        "Herbal Tea": "₹110",
        "Chai Latte": "₹120"
    },
    "Pastries & Snacks": {
        "Muffin": "₹70",
        "Croissant": "₹80",
        "Chocolate Cake": "₹90",
        "Sandwich": "₹120"
    }
}

todays_special = "Today's special is Hazelnut Mocha (₹170) and Spinach-Corn Sandwich (₹130)."

# --- Cafe Rules ---
rules = {
    ('hello', 'hi', 'hey', 'greeting', 'wassup'):
        ["Hello there! Welcome to our cafe. How can I help you today?", "Hi! What can I get for you?", "Hey! Good to see you."],
    ('thank', 'thanks', 'appreciate'):
        ["You're welcome!", "No problem! Enjoy your time here.", "Happy to help!"],
    ('bye', 'goodbye', 'exit', 'quit', 'see you'):
        ["Goodbye! Hope to see you again soon.", "Farewell! Have a wonderful day.", "Bye! Come back anytime."],
    ('menu', 'offer', 'serve', 'selection', 'list'):
        ["Here's our menu:\n\n" + "\n\n".join(
            [f"**{category}**\n" + "\n".join([f"- {item}: {price}" for item, price in items.items()])
             for category, items in menu.items()])],
    ('special', 'today', 'deal', 'promotion', 'combo'):
        [todays_special],
    ('coffee', 'brew', 'drip', 'filter', 'cup', 'espresso', 'americano', 'latte', 'cappuccino', 'mocha', 'macchiato', 'flat white'):
        ["We offer a variety of coffees:\n" + "\n".join([f"- {item}: {price}" for item, price in menu["Coffee"].items()])],
    ('tea', 'chai', 'herbal', 'green', 'black'):
        ["Our tea options include:\n" + "\n".join([f"- {item}: {price}" for item, price in menu["Tea"].items()])],
    ('food', 'eat', 'hungry', 'snack', 'pastry', 'cake', 'muffin', 'croissant', 'sandwich', 'bite'):
        ["Here's what we have to eat:\n" + "\n".join([f"- {item}: {price}" for item, price in menu["Pastries & Snacks"].items()])],
    ('wifi', 'internet', 'wi-fi', 'network', 'password'):
        ["Yes, we offer free WiFi. Network: 'CafeConnect_Guest', Password: 'enjoyyourcoffee'"],
    ('pay', 'payment', 'card', 'cash', 'credit', 'upi', 'gpay', 'paytm', 'phonepe', 'scan'):
        ["We accept cash, card, and UPI (GPay, PhonePe, Paytm)."],
    ('vegan', 'vegetarian', 'gluten-free', 'allergy', 'dairy-free', 'milk', 'soy', 'oat', 'almond'):
        ["We have options! We offer almond/oat milk and vegetarian items. Please inform us of any allergies."],
    ('restroom', 'bathroom', 'toilet', 'washroom', 'loo'):
        ["The restroom is at the back, past the counter to the left."],
    ('book', 'reservation', 'reserve', 'table'):
        ["We don't require reservations. Walk-ins are welcome!"],
    ('music', 'song', 'playlist', 'volume'):
        ["We play a curated playlist. Let us know if you'd like the volume adjusted."],
    ('hour', 'open', 'close', 'time', 'timing'):
        ["We're open from 8:00 AM to 8:00 PM daily."],
    ('location', 'address', 'where', 'find'):
        ["Our address: 15 Cafe Lane, Koregaon Park, Pune."],
    ('help', 'assist', 'support', 'question'):
        ["Sure! I can help you with menu, hours, WiFi, specials, and more."]
}

def get_response(user_input):
    lemmas = preprocess_text(user_input)
    for keywords, responses in rules.items():
        if any(keyword in lemmas for keyword in keywords):
            return random.choice(responses)
    return random.choice([
        "I'm sorry, I didn't quite get that. You can ask about our menu, coffee, hours, or WiFi.",
        "Hmm, not sure about that. Try asking about food, drinks, timings, or specials.",
        "I can best answer questions about coffee, tea, food, hours, location, and WiFi. Could you rephrase?"
    ])

# --- Streamlit UI Setup ---
st.set_page_config(page_title="Cafe Bot", layout="centered")
st.title("☕ Cafe Assistant Bot")

if "chat" not in st.session_state:
    st.session_state.chat = []

# Display chat history
for speaker, message in st.session_state.chat:
    with st.chat_message("assistant" if speaker == "Cafe Bot" else "user"):
        st.markdown(message)

# Handle new user input
user_input = st.chat_input("Ask something about our cafe...")

if user_input:
    st.session_state.chat.append(("User", user_input))
    if user_input.lower() == 'bye':
        response = "Goodbye! Hope to see you again soon."
    else:
        response = get_response(user_input)
    st.session_state.chat.append(("Cafe Bot", response))
    st.rerun()
