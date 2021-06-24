import discord
import time
from discord.ext import commands

client = commands.Bot(command_prefix = '.')
start = 0

def timeformat(time):
    hours = time//3600
    time -= hours * 3600
    minutes = time//60
    time -= minutes*60
    out = ''
    if(hours > 0):
        out += f'{hours} hours '
    if(minutes > 0):
        out += f'{minutes} minutes '
    return out + f'{time} seconds'


@client.event
async def on_ready():
    global start
    print('Bot online.')
    start = time.time()

@client.command()
async def uptime(ctx):
    await ctx.send(timeformat(int(time.time() - start)))

client.run('ODU3NDQzOTc2MTUxMTcxMDcy.YNPq7g.clYZVT5LEi6IirABTXL3IGCycUc')


#die scum