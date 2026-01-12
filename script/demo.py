from PIL import Image
import numpy as np
import sys

# CONFIGURATION
IMAGE_PATH = 'logo.jpg' # Put your image file name here
OUTPUT_WIDTH = 64               # Adjust this to change the mask size (larger = more detail)
THRESHOLD = 128                 # Adjust sensitivity (0-255) if the logo isn't appearing clearly

def generate_mask():
    try:
        # 1. Load image
        img = Image.open(IMAGE_PATH)
        
        # 2. Calculate new height to maintain aspect ratio
        w_percent = (OUTPUT_WIDTH / float(img.size[0]))
        h_size = int((float(img.size[1]) * float(w_percent)))
        
        # 3. Resize using NEAREST to keep edges sharp
        img = img.resize((OUTPUT_WIDTH, h_size), Image.Resampling.NEAREST)
        
        # 4. Convert to Grayscale
        img = img.convert('L')
        
        # 5. Binarize (Thresholding)
        # Assuming the logo is lighter than the background (Purple background = dark, Teal/White logo = light)
        # Pixels > THRESHOLD become 1, others 0
        fn = lambda x : 1 if x > THRESHOLD else 0
        img = img.point(fn, mode='1')
        
        # 6. Convert to Numpy Array
        arr = np.array(img, dtype=int)
        
        # 7. Print as C Array
        height, width = arr.shape
        print(f"// Generated Mask: {width}x{height}")
        print(f"#define YAPE_HEIGHT {height}")
        print(f"#define YAPE_WIDTH  {width}")
        print("int yape_shape[YAPE_HEIGHT][YAPE_WIDTH] = {")
        
        for row in arr:
            # Join the row data with commas
            row_str = ",".join(str(x) for x in row)
            print(f"    {{{row_str}}},")
            
        print("};")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    generate_mask()