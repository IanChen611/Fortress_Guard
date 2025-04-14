from PIL import Image
import os

# 原始圖片路徑
input_path = ".\Resources\Image\MiniWorld Sprites\Characters\Monsters\Slimes\Slime.png"
# 輸出資料夾路徑
output_folder = "./Resources/output_images/Slime"

# 建立輸出資料夾（若尚未存在）
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# 開啟原始圖片
with Image.open(input_path) as img:
    # 取得原始圖片大小
    width, height = img.size

    # 設定切割區塊大小
    tile_width = 16
    tile_height = 16

    # 計算可以切割幾列、幾行
    # （假設整張圖正好被16x16整除）
    rows = height // tile_height
    cols = width // tile_width

    # 逐列逐行切割
    for row in range(rows):
        for col in range(cols):
            # 計算對應切割區域的位置
            left = col * tile_width
            top = row * tile_height
            right = left + tile_width
            bottom = top + tile_height

            # 擷取該區域影像
            tile = img.crop((left, top, right, bottom))

            # 命名輸出的檔案：row_col.png
            tile_path = os.path.join(output_folder, f"tile_{row}_{col}.png")
            tile.save(tile_path, "PNG")

print("圖片切割完成！")
