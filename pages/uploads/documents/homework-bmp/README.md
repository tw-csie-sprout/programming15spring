# Bitmap 作業報告
資訊之芽
sprout AT csie.ntu.edu.tw

## 簡介

本次作業我實作了 Sobel filter，也另外產生了三種隨機圖片。Sobel filter 除了課堂上的原始版本，我也嘗試把運算結果疊加回原本圖片，模擬自動加邊框的效果。而另外三種隨機圖片都是以簡單圖形疊加的方式產生，前兩種是疊加基本幾何圖形，第三種是複製輸入的素材。

## 實作方法與結果
### Sobel Filter

Sobel filter 實作的結果如下圖。最左邊是原始圖片，經過 Sobel filter 運算的結果如中間。我同時也嘗試把 Sobel filter 產生的結果直接疊加到原始圖片的 B 分量，結果就像給原始圖片加上邊框，效果如右圖。

![Before Sobel Filter](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/flower_before.jpg) ![After Sobel Filter](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/flower_after.jpg) ![Variation: Add Edges](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/flower_variation.jpg)

對於一個像素 (x,y)，Sobel filter 需要使用 (x±1, y±1) 的像素計算變化值。為了方便，我忽略最外圍的一圈像素。而實際上 Sobel filter 算出來有相當多的雜訊（任何細微的變化都會有影響），因此我過濾掉所有不超過 60 的結果，如下：

```cpp
int threshold = 60;

int gx = ...;
int gy = ...;

buf_b[i][j] = ((int)std::sqrt(gx*gx + gy*gy))/threshold*threshold;
```

### 產生隨機圖片

我還另外產生了三種隨機的圖片。前兩種圖片都是直接疊加到黑底上的，不需要輸入檔。第三種則會從輸入檔擷取素材。

- 隨機疊加圓形

    ![Circle](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/random_circle.jpg)

    隨機產生的結果如上圖。這個圖形主要是希望不斷疊加圓形的**一部分**（而不是完整的圓形），因此產生亂數時事先隨機產生圓周上的點，再隨機產生半徑、夾角並計算圓心

    ```cpp
    int cy, cx;
    int radius = rand()%200 + 100;
    {
      int ty = std::rand() % bmp_size;
      int tx = std::rand() % bmp_size;
      double dir = (std::rand() % 360)*PI/180.0;
      cx = (int)(tx + std::cos(dir)*radius);
      cy = (int)(ty + std::sin(dir)*radius);
    }
    ```

    選用顏色疊加的方式是因為這樣可以產生幾何圖形中，不同封閉區塊顏色都不一樣的效果。

- 隨機疊加產生波浪

    ![Collage (I)](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/random_collage_1.jpg) ![Collage ()](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/random_collage_0.jpg) ![Collage (II)](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/random_collage_2.jpg)

    相反地，這個演算法疊加的是變形的「圓形」。原本的圓形半徑式子是

    r1(θ) = R （R 是隨機產生的常數）

    這次我們則會把半徑隨著該點與 x 軸的夾角做變化

    r2(θ) = R + Δ sin(Cθ) （R、Δ、C 都是隨機產生的常數）

    我產生許多這種小圖形，並疊加到畫布上。最終結果看起來有點像玻璃或水波。一開始產生的三張圖片中，最左邊與最右邊分別是改變顏色隨機產生的範圍造成不同的效果（`R,G,B <- 0..29` 與 `R,G,B <- 0..49` 的差異），中間則是把圖案再疊加到漸層色的背景上（背景是黑色從左到右漸層）。

    實際疊加圖樣時，我從畫布上的像素出發，以 (ox,oy) 為圓心，計算像素的座標 (x,y) 對 x 軸的夾角。有了夾角，就可以用 r2(θ) 計算半徑，並判斷 (x,y) 是否在圖案內部。

    ```cpp
    double theta = std::atan2(y-oy, x-ox) * wave;
    double changed_radius = std::sin(theta)*radius/var + radius;

    int dist2 = (y-oy)*(y-oy) + (x-ox)*(x-ox);
    if (dist2 <= changed_radius*changed_radius) {
      canvas_r[y][x] += r;
      canvas_g[y][x] += g;
      canvas_b[y][x] += b;
    }
    ```

- 隨機複製素材

    ![Leaves](http://tw-csie-sprout.github.io/programming15spring/pages/uploads/images/homework-bmp/random_leaf_out.jpg)

    這次嘗試中我把輸入的素材隨機貼到畫布上，分成許多層並調整相對應的亮度，產生如以上落葉的效果。與前兩次不同的是，這次顏色不再是疊加上去（因為不是透明色），而是直接覆蓋；同時，我們把黑色的背景去掉，忽略不複製。複製的虛擬碼如下：

    ```
    for round = 0 to T
       把畫布整體變暗（所以更之前貼上去的葉子會變暗）

       隨機貼上許多張樹葉，複製時：
          隨機計算圖片旋轉的角度、縮放
    ```

    此外，複製素材時，我忽略黑色的背景（就好像那是透明色）。

    ```cpp
    // 如果不是黑色，則覆蓋上顏色
    if (leaf_r[y][x] && leaf_g[y][x] && leaf_b[y][x]) {
      canvas_r[y0+dy][x0+dx] = leaf_r[y][x];
      canvas_g[y0+dy][x0+dx] = leaf_g[y][x];
      canvas_b[y0+dy][x0+dx] = leaf_b[y][x];
    }
    ```

## 結論

在本次作業中，Sobel filter 能夠計算出圖案大致的邊框。因為算出來有雜訊，我們可以把太維微細的變化過濾掉。

產生隨機圖片時，我發現透過疊加顏色而非直接設定顏色的方式，可以讓圖片的顏色看起來比較連續，不會有突兀的效果。同時這樣產生出來的圖片也有半透明的效果。隨機貼上素材圖時，則可以依層次調整亮度，也可以隨機修改圖片的縮放、旋轉角度等。
