import telegram

bot = telegram.Bot(token='')
bot_chatID = 
bot.send_message(chat_id=bot_chatID, text="Alarm!!")
bot.send_photo(chat_id=bot_chatID,photo=open('./image.jpg','rb'))
