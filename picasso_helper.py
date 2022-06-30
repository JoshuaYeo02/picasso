from PIL import Image, ImageDraw
from random import randint

''' Class to generate images'''
class PicassoTool:
    ''' Initalize Class fields'''
    def __init__(self, original_img):
        try:
            self.original_img = Image.open(original_img)
        except:
            print(f'{original_img} is not a valid path')
        self.frames = []
        self.width, self.height = original_img.size
        self.current_frame = Image.new('P', (self.width, self.height), (baseR, baseG, baseB))
        # Current score from current frame to original img
        self.current_score = calculate_score(current_frame)

    ''' Generates a circle of random size, loc and color '''
    def create_parent():
        return
        
    ''' Returns score between frame and original image '''
    def calculate_score(self, frame):
        return

    ''' Returns new frame based off original_img and current frame '''
    def generate_frame(self):
        return
    
    ''' Generate img going through iterations amount of evolution '''
    def generate_img(self, iterations):
        return
    
    ''' Exports all frames into a gif '''
    def export_gif(self):
        return
    
    ''' Exports current frame '''
    def export_frame(self):
        return
    
    ''' Exports frame "number" '''
    def export_frame(self, number):
        return