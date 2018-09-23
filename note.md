
//悔棋
//重新播放
//彩蛋


# 图形化界面开发工具 Qt


## 分工
 - 界面设计/贴图
 - 音效



 - Qt
   - 主页
   - 游戏界面
   - 排行榜
   - 自定义
 

- 游戏类｛
******
返回的地图信息
    // 1~8表示数字
    // 9表示空白
    // 10表示炸弹
    // 11表示未显示空白
    // 12表示未显示标记旗帜
    // 13表示未显示标记问号
****

 1. init 初始化游戏地图（输入长，宽，炸弹数量）｛
无返回值
｝

 2. reset 初始化游戏地图（重置本局）（不需要传入数据）｛
无返回值
｝

 3. 传入左键点击的格子的坐标（x,y）｛
返回 ｛更新后的地图，成功/失败状态，剩余雷的个数｝
｝

 4. 传入右键点击的格子的坐标（x,y）｛
返回 ｛更新后的地图，成功/失败状态，剩余雷的个数｝
｝

 5. 传入左右键同时点击格子的坐标（x,y)｛
返回 ｛更新后的地图，成功/失败状态，剩余雷的个数｝
｝

｝


结构体 a｛分数，名字，｝

排行榜类.1返回的结构体｛
	vector<a> b;
	a c;
｝

排行榜类.2返回的结构体｛
	vector<a> q1;
	vector<a> q2;
    vector<a> q3;
｝

- 排行榜类｛
 1. 插入数据（难度，分数，名字）｛
    写入文件
	返回全部的&位次&&当前位次，排名
｝
 2. 查询数据（难度）｛
	返回全部的
｝
 3. 初始化（读取文件）｛
    无返回值
｝
｝



 - 指定位置插入图片
 - 判断指定位置的点击
 - 对按键的反应


## 流程
- 菜单
   - //新手教程（待定
   - //难度
   - 主题列表
   - 排行榜
   - 开始游戏
   - 自定义

- 流程
   - 主题列表
   - 自定义
      - 宽度（9/）
      - 高度（9/）
      - 地雷数量（10/（宽-1）*（高-1））
      - 开始游戏（除选择难度）
   - 排行榜
      - 分栏显示所有难度
      - 返回主菜单
   - 开始游戏
      - 选择难度
      - 开始
      - 失败
         - 显示失败贴图
         - 统计信息
            - 时间
            - 标记正确的地雷
            - 解除的区域
         - 再来一次
            - 当前地图
            - 新地图	
         - 更改难度
         
      - 成功
         - 询问名字（默认Li_Hua）
         - 统计信息
            - 时间
            - 排行榜（预设难度
               - 我在排行榜中的位置
         - 再来一次
            - 当前地图
            - 新地图
         - 更改难度
       - 游戏中
         - 当前时间
         - 剩余雷数
         - 重新开始
            - 当前地图
            - 新地图
         - 返回到开始菜单
         - //教程
         
## 素材


- 音效
   - 开始音效
   - 点击
      - 左键
      - 右键
	  - 左右键同时按
   - 大面积消除
   - 爆炸
   - 失败（嘲讽
   - 胜利
   - 无效点击

- 贴图
   - 已知
     - 空白//01
     - 数字//02
     - 雷//03
   - 未知
     - 空白/选中//14、15高亮表示
     - 旗子/选中//04
     - 问号/选中//05
   - 背景//U1、U2、U3
   - 难度、时钟与地雷数量显示合为一个菜单//67
   - 爆炸效果//08
   - 重玩此局按钮//09
   - 重新开始新关卡//10
   - 返回主菜单//11
   - 菜单（激活/未激活）//12、13
   - 游戏区域半透明底板//16