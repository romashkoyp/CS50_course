# Get greeting
answer = input("Greeting: ")
x = answer.strip().lower()

# condition 1 if hello $0
if x.startswith("hello"):
    print("$0")
# condition 2 if h $20
elif x.startswith("h"):
    print("$20")
# condition 3 else $100
else:
    print("$100")