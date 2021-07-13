ans = 'Y'
items = []
prices = []

while not ans == 'N':
    items.append(input('Enter name of candy: '))
    prices.append(float(input('Enter price of candy: $')))
    ans = input('Enter another candy (Y/N)')

avgprice = sum(prices)/len(prices)
cheapest = prices.index(min(prices))
m_expensive = prices.index(max(prices))

print(f'\nAverage Price: ${format(avgprice, ".2f")}')
print(f'Cheapest Item: {items[cheapest]} at ${format(prices[cheapest], ".2f")}')
print(f'Most Expensive Item: {items[m_expensive]} at ${format(prices[m_expensive], ".2f")}')

