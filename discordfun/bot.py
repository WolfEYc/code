from asyncio import tasks
import discord
import time
from discord.message import Attachment
import youtube_dl
from discord import channel
from discord.ext import commands, tasks
import datetime
import scheduler


bot = commands.Bot(command_prefix = '.')
start = 0
linked_channels = {}

def chop_microseconds(delta):
    return str(delta - datetime.timedelta(microseconds=delta.microseconds))

def getUptime():
    return chop_microseconds(datetime.datetime.now() - start)

async def sendMsg(channel, message):
    await channel.send(f'{message.author}: {message.content}')
    for attachment in message.attachments:
        await channel.send(attachment)

def strMsg(message):
    msg = f'{datetime.datetime.now()} : {message.author} : {message.content}'
    for attachment in message.attachments:
        msg += '\n' + str(attachment)
    return msg

@bot.event # Readying up
async def on_ready():
    global start
    notifs.start()
    print('Bot online.')
    start = datetime.datetime.now()

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

'''
@bot.command()
async def add(ctx, *args):
    if len(args) != 3:
        await ctx.send("Enter as name start end\nDate Format: mm-dd hh:mm military time")
        return
    name = args[0]
    s_date = datetime.datetime.strptime(args[1], "%m-%d-%H:%M")
    e_date = datetime.datetime.strptime(args[2], "%m-%d-%H:%M")
    schedulebot.add(name, {s_date, e_date})
    await ctx.send(f'Session added for {name} on {s_date.strftime("%m-%d")} from {s_date.strftime("%H:%M")} to {e_date.strftime("%H:%M")}')
'''

@tasks.loop(seconds = 5)
async def notifs():
    for serv, channel in linked_channels.items():
        await channel.send('my balls')
    



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


bot.run('ODU3NDQzOTc2MTUxMTcxMDcy.YNPq7g.ciMALfDvQe08WYFKlfU-tEwbEVo')

