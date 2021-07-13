cars = [{'name': 'mercedes benz e350', 'price': 58825, '0-60': 6.0, 'doors': 4}, {'name': 'volkswagen beetle', 'price': 22000, '0-60': 7.5, 'doors':2}, {'name':'mini cooper', 'price': 19750, '0-60': 5.5, 'doors':2}, {'name':'BMW 428i', 'price':45600, '0-60':5.7, 'doors':2}, {'name':'Ford Mustang', 'price':32655, '0-60':4.5, 'doors':2 }, {'name':'Camaro', 'price':25000, '0-60': 5.4, 'doors':2}, {'name' :'Fiat 500', 'price':22250, '0-60':9.4, 'doors':2},
 {'name':'BMW 328i', 'price': 69900, '0-60':4.0, 'doors':4 }, {'name':'Lexus 250c', 'price':43660, '0-60':7.6, 'doors':2}, {'name':'Rolls Royce Dawn', 'price':356000, '0-60':4.3, 'doors':2}, {'name':'Porche 911 Carrera', 'price':101200, '0-60':3.0, 'doors':2}, {'name':'Maseratti Grancabrio', 'price':150380, '0-60':4.7, 'doors':2}, {'name':'Dai-copen', 'price':22370, '0-60':9.2, 'doors':2}, {'name':'Fiat 124 Spider', 'price':26840, '0-60':6.9, 'doors':2}, {'name':'Ford Fairlane 500 Skyliner', 'price':44779, '0-60':9.6, 'doors':2}, {'name':'Aston Martin Vanquish', 'price':212486, '0-60': 4.3, 'doors':2}, {'name':'mercedes bendz slk', 'price':49550, '0-60':4.3, 'doors':2},
 {'name':'Porche 718 boxter', 'price':62600, '0-60': 4.4, 'doors':2}, {'name':'BMW z4', 'price':49700, '0-60':3.8, 'doors':2}, {'name':'BMW 2 Series', 'price':49700, '0-60':5.45, 'doors':4}, {'name':'Mazda miata', 'price':26830, '0-60':5.7, 'doors':2}, {'name':'Jaguar XK', 'price':35988, '0-60':5.3, 'doors':2}, {'name':'Jeep Wrangler', 'price':28295, '0-60':15, 'doors':4}, {'name':'Range Rover Evoke', 'price':44000, '0-60':10.3, 'doors':4}, {'name':'TVR chimera', 'price':19995, '0-60':4.6, 'doors':2}, {'name':'MGB', 'price':116000, '0-60':10, 'doors':2}, {'name':'Triumph Spitfire', 'price':19600, '0-60':13, 'doors':2}]

q1 = int(input('price: '))
q2 = int(input('doors: '))
q3 = float(input('0-60: '))

our_car = {}

for car in cars:
    if car['price'] == q1 and car['doors'] == q2 and car['0-60'] == q3:
        our_car = car

if len(our_car) == 0:
    print('Did not find car')
elif our_car['0-60'] <= 4.0:
    print(our_car['name'], 'is fast!!!')
else:
    print(our_car['name'])
