from PIL import Image, ImageDraw
from random import randint

frames = []
width, height = 1920, 1080
baseR, baseG, baseB = 128, 128, 128

im = Image.new('RGB', (width, height), (baseR, baseG, baseB))
draw = ImageDraw.Draw(im)
frame = im.copy()
frame = frame.quantize(method=Image.MEDIANCUT)
frames.append(frame)

for _ in range(50):
    ranX = randint(0, width)
    ranY = randint(0, height)
    ranR = randint(0, max(width, height)/2)
    colR, colG, colB = randint(0, 225), randint(0, 255), randint(0, 255)
    draw.ellipse((ranX - ranR, ranY - ranR, ranX + ranR, ranY + ranR), fill=(colR, colG, colB))
    frame = im.copy()
    frame = frame.quantize(method=Image.MEDIANCUT)
    frames.append(frame)

frames[5].save('img/pillow_demo.png', quality = 100)
frames[0].save('img/pillow_gif_demo.gif',  save_all=True, append_images=frames[1:], optimize=False, duration=100, loop=0, quality = 100)