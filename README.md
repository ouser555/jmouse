# jmouse

* qmk 0.26.10

* hardware
  * 1rp2040 zero moudle
  * 11keys
  * 1joystick
  * 1encoder
  * 1 0.91" oled
  * 1 adns5050 optical sensor
  * 1 scroll encoder

* make jmouse:via

* 分享一下自己改的左手直立式滑鼠，應該也算是鍵盤吧

  原本是使用delux的直立式滑鼠，但嫌它按鍵實在太少，沒辦懶人操作，市面上也沒有左手直立多鍵，所以自己用qmk製作了一個。

  由於要做到手掌的人體工學要花費大量的時間，考慮過後就找現成的模型來remix。

  

主要是用logitech的vertical mouse和the cat keyboard網上分享的模型去改的
![image](https://github.com/ouser555/jmouse/blob/main/pic/001.jpg)
硬是給他加上了滑鼠滾輪OLED和12個MX軸，還用上了熱插拔


![image](https://github.com/ouser555/jmouse/blob/main/pic/002.jpg)
從這個角度看外觀看起來還行


![image](https://github.com/ouser555/jmouse/blob/main/pic/003.jpg)
光學傳感器則用簡單的ADNS-5050，這里抄the cat keyboard的方式，直接用手焊零件，這個機構可以360度任意調整傳感器的方向。


![image](https://github.com/ouser555/jmouse/blob/main/pic/005.jpg)
拇指區則學Azeron做了一個可調角度的joystick，和5向鍵，因為空間的關係使用較薄的joycon。


![image](https://github.com/ouser555/jmouse/blob/main/pic/006.jpg)
高特的熱插拔，只用二極體的針腳就完成矩陣電路。


![image](https://github.com/ouser555/jmouse/blob/main/pic/004.jpg)
主控用waveshare的rp2040 zero，自以為很巧妙的把它裝在前端。並露出設定鍵的孔位。


這個我自己使用一陣子了，所以底部看起來有點髒。



* 原本因為自己不知道這個vertical mouse的模型是否合自己的手掌， 所以改模型改得很隨便，只要求能夠做完整的功能測試即可，定位鎖孔那些都沒有好好完成， 好幾個地方我都只用熱溶膠固定，鍵盤背板也沒有封，飛線直接露出。

* 自己使用了一陣子，最近因為覺得這個項目不會再繼續了，所以就把這個半成品的模型分享出來， 這也不是能隨插即用的狀態，但是我想可能對一些人會有幫助。



* 補一點簡短的使用心得:

  用鍵盤機械軸體替代滑鼠的微動開關， 剛開始就是不習慣，機械軸的行程與微動開關相比，長了非常多，體感非常明顯。 但用幾天後就習慣了，但我不知道其他人是否能夠習慣。

  我原本就有在使用delux的直立式滑鼠， 這個logitech的vertical mouse的模型對我來說用起來感覺則更好，但這也是因人而異。

  拇指操作joystick我原本想說是個很騷包的設計，最後我只拿來控制滾輪， 而且還是用按鍵模擬的方式，根本就浪費了這個joycon。

  雖然有12個按鍵，但越往手掌內側的位置越不容易按到，甚至有幾個鍵自己是棄用的。



* 講完收工，最後附上模型連結，是放在printables上的

  https://www.printables.com/model/730351-jmouse
