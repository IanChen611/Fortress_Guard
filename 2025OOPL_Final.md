# 2025 OOPL Final Report

## 組別資訊

組別：28
組員：112820003辛政隆、112820025陳翊揚
復刻遊戲：國王保衛戰

## 專案簡介

### 遊戲簡介
> 要塞守護是一款類似`國王保衛戰`，放置守護者來攻擊怪物，擊敗怪物後獲得的金幣可以購買新的守護者或是升級守護者。隨者敵人波數及關卡難度增加，怪物的血量及數量也會增加，還會出現不同型態的敵人。</br>
特色在於多種進攻路線與隨關卡變化的地形限制，考驗玩家配置與資源分配策略。

### 組別分工
| 工作項目 | 112820003 辛政隆 | 112820025 陳翊揚|
|----------|------------------------------|----------------------------------|
| 地圖製作 | 研究如何使用Tiled、利用製作Tile、收集圖片檔案 | 設計地圖、轉換成地圖代碼           |
| 物件製作 | 製作 Guard、Enemy             | 製作 SceneManager、UI 類別(Button、Heart)      |
| 讀檔製作 | 設計 ReadEnemy、ReadWaypoint  | 製作 Read 相關架構                |
| 關卡製作 | 設計敵人種類及波數             | 製作關卡 UI                       |
| 動畫製作 | 整理並切割找到的素材圖片        | 製作子彈及角色動畫                 |



## 遊戲介紹

### 遊戲規則
我們有製作遊戲說明，可以點擊`遊戲說明`查看以下內容。</br>
![教學頁面P1](./Resources/Image/UI/Tutorial_1.png)
![教學頁面P2](./Resources/Image/UI/Tutorial_2.png)
![教學頁面P3](./Resources/Image/UI/Tutorial_3.png)
![教學頁面P4](./Resources/Image/UI/Tutorial_4.png)

### 遊戲畫面
> **遊戲首頁**，點擊`開始遊戲`進入關卡選擇畫面，點擊`遊戲說明`可以進入教學說明。
![首頁](./Resources/Image/UI/gamingPage1.png)

> **選擇關卡畫面**，有1~15關以及無盡模式，共16種關卡
![關卡畫面](./Resources/Image/UI/gamingPage2.png)

> **這是遊戲畫面(以第二關舉例)**
![關卡畫面](./Resources/Image/UI/gamingPage3.png)

## 程式設計

### 程式架構
```mermaid
graph TD


  GameObject --> Guard
  GameObject --> Enemy
  GameObject --> TileSet
  GameObject --> Tile
  GameObject --> Ui

  Ui --> Button
  Ui --> Heart
  Ui --> Money

  Scene --> ChooseLevelScene
  Scene --> Level
  Scene --> TutorialScene
  Scene --> StartScene

  SceneManager
  ReadWayPoint
  ReadMap
  ReadEnemy
  

  Guard --> Swordsman
  Guard --> Mage
  Guard --> Musketeer
  Guard --> Dragon
  Guard --> Market["Market<br>(can't attack)"]


  Enemy --> Slime["Slime<br>(easy quickly)"]
  Enemy --> MegaSlime["MegaSlime<br>(normal slow split)"]
  Enemy --> KingSlime["KingSlime<br>(strong very  slow split)"]
  Enemy --> Orc["Orc<br>(strong)"]
  Enemy --> Mammoth["Mammoth<br>(fast)"]
  Enemy --> Necromancer["Necromancer<br>(very slow, summon)"]

```

### 程式技術
1. **CSV 資料載入器 (ReadWaypoint、ReadEnemy、ReadMap)**
  > - 利用 STL `ifstream` + `stringstream` 實作通用 CSV 解析器，配合 RAII 自動關閉檔案。
  > - 在`ReadMap`內可讀取事先製作的地圖代碼，讓我們可以直接套用事先切割好的圖，並且可以更方便設計、修改地圖。
  > - 在`ReadWaypoint`內採用儲存巢狀 `std::vector`，來儲存事先規劃好的不同路線。
  > - 在`ReadEnemy`上支援可以分辨不同的敵人種類以及不同路線，讓我們創造關卡時，可以在敵人種類、敵人進攻路線上更多元，坐起來也更方便修改。
2. **事件驅動 UI 與 Lambda Callback**
  > - UI 採事件驅動設計，`Button` 內部綁定 lambda callback，提高此物件的複用度。
  > - 每個按鈕只會注意自身行為，畫面與邏輯鬆耦合，方便最後把 UI 套件化。
  > - UI 成為父類別，將所有物件丟進一個UI的vector當中一起渲染。

3. **可調倍速的遊戲時鐘**
  > - `gameSpeed` 影響所有與時間有關的計數器（Wave 間隔、子彈冷卻…），點擊 UI 即時在 1×/2× 間切換。
  > - 不增加GPU負擔、利用乘法的方式讓冷卻減半 or 攻速加倍。


## 結語

### 問題與解決方法
### 自評

| 項次 | 項目                   | 完成 |
|------|------------------------|-------|
| 1    | 完成專案權限改為 public |    |
| 2    | 具有 debug mode 的功能  |    |
| 3    | 解決專案上所有 Memory Leak 的問題  | ✔ |
| 4    | 報告中沒有任何錯字，以及沒有任何一項遺漏  |  |
| 5    | 報告至少保持基本的美感，人類可讀  | ✔ |

### 心得
### 貢獻比例