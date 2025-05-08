import nltk
from nltk.chat.util import Chat, reflections
import re

# Sample pairs with patterns and responses
pairs = [
    [
        r"my name is (.*)",
        ["Hello %1, it's nice to meet you! How can I assist you today?", "Hi %1, how can I help you today?"]
    ],
    [
        r"hi|hello|hey there|hola",
        ["Hello, it's great to see you! What can I do for you today?", "Hi there! How can I assist you today?"]
    ],
    [
        r"what is your name ?",
        ["You can call me Claude. How can I assist you today?", "I'm Claude. What can I do for you today?"]
    ],
    [
        r"how are you ?",
        ["I'm doing well, thank you! How about you?", "I'm good, thanks for asking! How can I assist you today?"]
    ],
    [
        r"sorry (.*)",
        ["It's alright, no worries.", "That's okay, don't worry about it."]
    ],
    [
        r"I am fine",
        ["Great to hear that! How can I assist you today?", "That's good to hear. What can I do for you?"]
    ],
    [
        r"I (.*) good",
        ["That's great! How can I assist you today?", "Good to hear that. What can I do for you?"]
    ],
    [
        r"(.*) age?",
        ["Well, in digital years, I'm quite young!", "Age is just a number, especially for a bot like me!"]
    ],
    [
        r"what (.*) want ?",
        ["I'm here to assist you. What can I help you with today?", "My goal is to be helpful to you. What can I do for you today?"]
    ],
    [
        r"(.*) created ?",
        ["I was created by a team of developers.", "A team of programmers put their effort into creating me."]
    ],
    [
        r"(.*) (location|city) ?",
        ["I exist in the digital world, so I don't have a physical location.", "I'm based in the cloud, ready to assist you wherever you are."]
    ],
    [
        r"how is weather in (.*)?",
        ["I'm sorry, I can't provide real-time data as I don't have access to live databases.", "Unfortunately, I can't provide weather updates as I don't have access to real-time information."]
    ],
    [
        r"i work in (.*)?",
        ["%1 sounds like a great place to work. How can I assist you today?", "%1? That's interesting. How can I help you with your work?"]
    ],
    [
        r"(.*)raining in (.*)",
        ["I'm sorry, I can't provide real-time data as I don't have access to live databases.", "Unfortunately, I can't provide weather updates as I don't have access to real-time information."]
    ],
    [
        r"how (.*) health(.*)",
        ["I'm always operational and ready to assist you!", "I'm in top shape! Ready to assist you."]
    ],
    [
        r"(.*) (sports|game) ?",
        ["I can provide information on many sports. Which one are you interested in?", "I can help you find information about various games. Which one do you want to know about?"]
    ],
    [
        r"who (.*) sportsperson ?",
        ["There are many great sportspeople out there. Could you specify the sport?", "There are numerous talented athletes in various sports. Could you please specify the sport?"]
    ],
    [
        r"who (.*) (moviestar|actor)?",
        ["There are many talented actors in the film industry. Could you specify which film industry you're interested in?", "There are numerous talented moviestars. Could you please specify the country or the film industry?"]
    ],
    [
        r"i am looking for online guides and courses to learn data science, can you suggest?",
        ["Sure, there are many online platforms that offer courses in data science. Some of them include Coursera, edX, and Udacity.", "Absolutely, you can check out data science courses on platforms like Coursera, edX, and Udacity. They offer a variety of courses from beginner to advanced levels."]
    ],
    [
        r"(.*)",
        ["I'm not sure I understand. Could you rephrase that?", "Can you give me a bit more detail, please?"]
    ],
    [
        r"quit|exit|bye",
        ["It was nice talking to you. Have a great day!", "Goodbye! Don't hesitate to return if you have more questions."]
    ],
]

# Custom function to handle case-insensitive matching for 'quit', 'exit', 'bye'
def case_insensitive_converse():
    print("Hey there! I am Claude at your service. How can I assist you today?")
    chat = Chat(pairs, reflections)

    while True:
        user_input = input("> ").lower()  # Convert input to lowercase for case-insensitive matching
        if re.match(r"(quit|exit|bye)", user_input):  # Match common exit keywords
            print("Goodbye! Don't hesitate to return if you have more questions.")
            break
        response = chat.respond(user_input)
        if response:
            print(response)
        else:
            print("I'm not sure I understand. Could you rephrase that?")

# Start the chatbot
if __name__ == "__main__":
    case_insensitive_converse()
