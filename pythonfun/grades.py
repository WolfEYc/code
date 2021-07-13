quizes = []
mprojects = []


for i in range(1,11):
    grade =  int(input(f'Please enter grade for quiz #{i}: '))
    while grade < 0 or grade > 10:
        grade =  int(input(f'Make sure input is 0-10: '))
    quizes.append(grade)


for i in range(1,11):
    grade =  int(input(f'Please enter grade for mini-project #{i}: '))
    while grade < 0 or grade > 10:
        grade =  int(input(f'Make sure input is 0-10: '))
    mprojects.append(grade)

sumQuizes = sum(quizes)
sumMini = sum(mprojects)
sumTotal= sumMini+sumQuizes

print(f'The total point value for your quizzes is: {sumQuizes}')

print(f'Quiz grade percentage is: {sumQuizes}%')

print(f'The total point value for your mini-projects is: {sumMini}')

print(f'Mini-project grade percentage is: {sumMini/2}%')

print(f'The total point value for your quizzes and mini-projects is: {sumTotal}')

print(f'Grade percentage for mini-projects and quizzes is: {sumTotal/3}%')
