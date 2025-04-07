import random
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB

# Sample training data
training_data = {
    # Greetings
    "hi": "Hello! I'm your medical assistant.",
    "hello": "Hi! How can I help you today?",
    "good morning": "Good morning! How can I assist you?",
    "good evening": "Good evening! What symptoms are you experiencing?",

    # Fever
    "i have a fever": "You should rest and stay hydrated. If it continues, consult a doctor.",
    "running high temperature": "Monitor your temperature and stay hydrated. If it’s above 102°F, seek medical advice.",
    "fever and chills": "You might have an infection. Please consult a healthcare provider if it lasts more than 2 days.",

    # Cough
    "what to do for cough": "Try warm fluids and rest. If it persists, see a physician.",
    "dry cough and sore throat": "Warm salt water gargle and throat lozenges may help. Stay hydrated.",
    "persistent cough": "Persistent cough may need further evaluation. Please consult a doctor.",

    # Cold and flu
    "i have cold": "Stay warm, drink fluids, and rest. Consider taking vitamin C.",
    "sneezing and runny nose": "You may have a common cold or allergies. Rest and drink plenty of water.",
    "flu symptoms": "Rest, fluids, and over-the-counter medicine may help. If severe, consult a physician.",

    # Headache
    "i have a headache": "Take rest in a quiet place and drink water. If it's frequent, consult a neurologist.",
    "migraine problem": "Avoid bright lights and get rest. Consult a neurologist for proper treatment.",
    "headache and nausea": "These could be signs of a migraine. Consider seeing a doctor.",

    # Stomach issues
    "stomach pain": "Try to eat light food. If pain continues, visit a gastroenterologist.",
    "nausea and vomiting": "You might have food poisoning. Stay hydrated and consult a doctor if needed.",
    "i have indigestion": "Eat smaller meals, avoid spicy food, and take antacids if needed.",

    # COVID-related
    "covid symptoms": "Fever, cough, and breathing difficulties are common symptoms. Please get tested.",
    "tested positive for covid": "Isolate yourself, monitor your oxygen levels, and consult a doctor immediately.",
    "loss of smell and taste": "These are common COVID-19 symptoms. Please take a test and isolate.",

    # Skin issues
    "i have a rash": "Rashes can be due to allergies or infections. Avoid scratching and see a dermatologist.",
    "itchy skin": "Apply moisturizer or anti-itch cream. If it spreads, consult a skin specialist.",
    "pimples on face": "Maintain good hygiene, avoid oily food, and consult a dermatologist for treatment.",

    # Muscle / Body pain
    "body pain and fatigue": "You might be overworked or have viral infection. Take rest and hydrate.",
    "muscle pain after workout": "That’s normal. Use ice packs and rest the muscles.",
    "joint pain": "Consider using a hot compress and consult an orthopedic if pain persists.",

    # Ending / Politeness
    "bye": "Take care! Goodbye!",
    "thank you": "You're welcome! Feel better soon.",
    "thanks a lot": "Happy to help! Get well soon.",
    "exit": "Goodbye! Reach out if you need more help.",
}

# Data preparation
X_train = list(training_data.keys())
y_train = list(training_data.values())

# Vectorizer and model
vectorizer = TfidfVectorizer()
X_train_vec = vectorizer.fit_transform(X_train)

model = MultinomialNB()
model.fit(X_train_vec, y_train)

# Chat loop
def chatbot():
    print("🤖 MedicalBot: Hello! I'm your medical assistant. Type 'exit' to end.")
    while True:
        user_input = input("You: ")
        if user_input.lower() in ['exit', 'quit', 'bye']:
            print("🤖 MedicalBot:", training_data["bye"])
            break
        user_input_vec = vectorizer.transform([user_input])
        prediction = model.predict(user_input_vec)
        print("🤖 MedicalBot:", prediction[0])

if __name__ == "__main__":
    chatbot()
