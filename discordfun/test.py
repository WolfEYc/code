import discord
import time
from discord.message import Attachment
import youtube_dl
from discord import channel
from discord.ext import commands
from datetime import datetime

bot = commands.Bot(command_prefix = '.')
start = 0
linked_channels = {}

def getDate():
    return datetime.now().strftime("%Y-%m-%d %H:%M:%S")

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

def getUptime():
    return timeformat(int(time.time() - start))

async def sendMsg(channel, message):
    await channel.send(f'{message.author}: {message.content}')
    for attachment in message.attachments:
        await channel.send(attachment)

def strMsg(message):
    msg = f'{getDate()} : {message.author} : {message.content}'
    for attachment in message.attachments:
        msg += '\n' + str(attachment)
    return msg


@bot.event # Readying up
async def on_ready():
    global start
    print('Bot online.')
    start = time.time()

@bot.event # Message Logging
async def on_message(message):
    server = message.guild
    if(message.author != bot.user):
        print(strMsg(message))
        if(server in linked_channels and linked_channels[server] == message.channel):
            for serv, channel in linked_channels.items():
                if(serv != server):
                    await sendMsg(channel, message)              

    await bot.process_commands(message)

@bot.command() # .uptime command
async def uptime(ctx):
    await ctx.send(getUptime())

@bot.command()
async def link(ctx):
    server = ctx.message.guild
    chat_channel = ctx.message.channel
    linked_channels[server] = chat_channel
    await ctx.send('chatman is linked!')

@bot.command()
async def unlink(ctx):
    server = ctx.message.guild
    if(server in linked_channels):
        linked_channels.pop(server)
        await ctx.send('chatman is unlinked!')
    else:
        await ctx.send('link me first!')

''' audio support
@bot.command()
async def join(ctx): # makes bot join vc
    if(ctx.author.voice):
        channel = ctx.message.author.voice.channel
        await channel.connect()
    else:
        await ctx.send("join vc first homie")

@bot.command()
async def dc(ctx):
    if(ctx.voice_client):
        await ctx.guild.voice_client.disconnect()
        await ctx.send('adios')
    else:
        await ctx.send(f'{ctx.message.author.mention} dc from what bro?')

@bot.command()
async def load(ctx, extension):
    server = ctx.message.server
    voice_client = ctx.guild.voice_client
'''


bot.run('ODU3NDQzOTc2MTUxMTcxMDcy.YNPq7g.HHKbv_yMEXcCvcAwZMJ4_voVE58')


#die scum