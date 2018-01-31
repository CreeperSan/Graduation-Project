## 毕业设计 - 农业温室大棚

快毕业了，是时候准备毕业设计了，这里记录了咱毕业设计的全部内容以及源代码

具体功能是是通过STM32与传感器与控制器联动，进行控制，并将数据传输到树莓派中的数据库存起来，并且对外提供一个WEB服务器和API，可以通过浏览器和客户端进行控制访问和联动

### 当前进度
#### 后台服务器/数据库
1. URL定向 ... (80%)
2. 数据库设计 ... (完成)
3. 用于APP的登录认证 ... (0%)
4. 用于Web的登录认证 ... (90%)
4. 配置文件的读写保存 ... (完成)
5. 历史记录功能 ... (0%)
6. 定时 ... (未开始)

#### Web
1. 用户 ... (80%)
2. 管理与配置 ... (完成)
3. 用户管理 ... (70%)
4. 历史记录查看 ... (20%)
5. 定时 ... (0%)

#### Android
1. UI界面 ... (0%)
2. 登录验证保存 ... (0%)
3. 配置与控制 ... (0%)
4. 定时 ... (0%)
5. 用户管理 ... (0%)
6. 报警通知 ... (0%)

#### 嵌入式
1. STM32的传感器信息读取 ... (30%)
2. STM32的外设控制 ... (20%)
3. 树莓派与STM32的交互 ... (0%)
4. 域名 ... (0%)
5. 内网穿透 ... (0%)

### 功能
1. 远程监视控制大棚情况
2. 异常报警与异常阈值调节
3. 定时任务
4. 历史记录
5. 报警提醒
6. 多用户管理

### 进度展示
![](screenshot/web0001.png)
![](screenshot/web0002.png)
![](screenshot/web0003.png)
![](screenshot/web0004.png)
![](screenshot/web0005.png)
![](screenshot/web0006.png)
 


