# BÁO CÁO DỰ ÁN LẬP TRÌNH

## 1. Hướng dẫn cài đặt (cho HĐH Windows)
  - Bước 1: Chuyển repo này về tài khoản cá nhân.
  - Bước 2: Clone repo về máy tính cá nhân bằng lệnh git clone https://github.com/[USER_NAME]/Game_SDL
  - Bước 3: Sử dụng Visual Studio và chạy file Game_SDL.sln
  - Bước 4: Chạy chương trình bằng cách sử dụng tổ hợp phím CTRL + F5
  
  
## 2. Tổng quan về trò chơi
  - Trò chơi được lấy ý tưởng chính từ tựa game có tên Evergate.
  - Cốt truyện của trò chơi xoay quanh 1 nhân vật vượt qua các màn chơi và thu thập các vật phẩm để tìm lại ký ức.
  - Mỗi màn chơi sẽ có các địa hình khác nhau, các cơ chế (vd: cơ chế dịch chuyển) khác nhau, đòi hỏi người chơi phải suy nghĩ và di chuyển đưa nhân vật tới vị trí đích.
  - Với mỗi lần nhân vật rơi xuống vực nhân vật sẽ trở lại 1 điểm Save Point mà nhân vật đã đi qua trước đó. Vì vậy nếu có rơi xuống vực thì cũng chưa phải là kết thúc. Tuy nhiên cần phải cẩn trọng và nhanh chóng di chuyển để tránh bị Fire wall đuổi kịp. Fire wall (tường lửa) sẽ bắt đầu di chuyển sau 1 thời gian sau khi màn chơi bắt đầu với 1 tốc độ không đổi. Nếu người chơi bị nó đuổi kịp thì GAME OVER!.
  - Người chơi không nhất thiết phải thu thập toàn bộ vật phẩm trong màn. Các vật phẩm có tác dụng mở khoá các thành tựu từ đó mở khoá các chương mới và mở khoá thêm các tính năng. Tuy nhiên để qua màn thì chỉ cần đến được vị trí đích.
  - Dự án hiện tại chỉ xây dựng 1 màn chơi. Việc xây dựng nhiều màn chơi tiếp theo sẽ được phát triển trong tương lai.
  
  
## 3. Các chức năng trong trò chơi
  
## 4. Các Kỹ thuật lập trình được sử dụng trong trò chơi
  - Kỹ thuật lập trình hướng đối tượng: Trò chơi được chia thành nhiều đối tượng khác nhau để dễ dàng quản lý và sử dụng. Có tận dụng tất cả tính năng của lập trình hướng đối tượng bao gồm tính kế thừa, tính đóng gói, tính đa hình.
  - Kỹ thuật chia tách file: Các Class được khai báo trong các file .h và việc định nghĩa chi tiết các phương thức của class được đưa vào trong các file .cpp
  - Sử dụng cấu trúc Struct: Trong khi các đối tượng có độ phức tạp cao (nhiều thuộc tính, nhiều phương thức) được quản lý thông qua các Class thì các đối tượng ít phức tạp (như đối tượng vị trí chỉ gồm toạ độ x và y) được quản lý thông qua struct.
  - Sử dụng cấu trúc mảng: Trong dự án có sử dụng container vector C++ để lưu trữ các đối tượng.
  - Kỹ thuật quản lý tệp: Một số dữ liệu được nhập vào từ các tệp .dat hoặc .txt
  - Đồ hoạ với thư viện SDL:
    * Kỹ thuật load ảnh
    * Kỹ thuật render ảnh
    * Kỹ thuật sử dụng frame tạo hiệu ứng chuyển động
    * Kỹ thuật sử dụng GameLoop
    * Kỹ thuật sử dụng cấu trúc SDL_Rect
    * Kỹ thuật Tile map
    * Kỹ thuật xử lý va chạm nhân vật
    * Kỹ thuật vẽ hình chữ nhật đặc
  
  - Âm thanh với thư viện SDL:
    * Kỹ thuật load âm thanh 
    * Kỹ thuật phát file .wav và .mp3
   
  - Kỹ thuật clean code.
  
  - Note:
    * Các kỹ thuật ứng dụng từ khoá học: Kỹ thuật lập trình hướng đối tượng, Kỹ thuật chia tách file, Sử dụng cấu trúc Struct, Kỹ thuật load ảnh, Kỹ thuật render ảnh, Kỹ thuật sử dụng GameLoop, Kỹ thuật vẽ hình chữ nhật đặc, Kỹ thuật clean code.
  
    * Các kỹ thuật học từ web [phattrienphanmem123az.com](https://phattrienphanmem123az.com/): Kỹ thuật load ảnh, Kỹ thuật render ảnh, Kỹ thuật sử dụng frame tạo hiệu ứng chuyển động, Kỹ thuật sử dụng cấu trúc SDL_Rect, Kỹ thuật Tile map, Kỹ thuật xử lý va chạm nhân vật.
  
    * Các kỹ thuật học từ web [stdio.vn ](https://www.stdio.vn/): Kỹ thuật sử dụng GameLoop, Kỹ thuật load âm thanh, Kỹ thuật phát file .wav và .mp3
    
    * Các Kỹ thuật học được từ [Stackoverflow](https://stackoverflow.com/): các fix một số lỗi.
    
## 5. Kết luận, hướng phát triển và kinh nghiệm rút ra
  - Kết luận:
    * Dự án hoàn thành trong thời gian 4 tuần (từ tuần học thứ 11 đến 22/05/2022).
    * Dự án có ứng dụng nhiều kỹ thuật lập trình từ các nguồn khác nhau.
    * Dự án tạo ra một trò chơi có âm thanh, đồ hoạ và có tiềm năng phát triển tiếp.
 
  - Huóng phát triển tiếp theo:
    * Sửa lại hình ảnh của một số đối tượng để đối tượng trở nên đẹp hơn, không bị rời rạc.
    * Thêm bộ đếm thời gian và tính năng paused game.
    * Tạo ra thêm các màn chơi mới.
    * Tạo ra các cơ chế mới cho trò chơi (VD như cơ chế địa hình có thể di chuyển, cơ chế kích hoạt tính năng ẩn của địa hình v.v)
    * Tạo ra hệ thống thành tựu cho phép mở khoá màn chơi mới và thêm các tính năng để người chơi có thể chọn 1 trong nhiều tính năng hỗ trợ giúp việc qua màn trở nên dễ dàng (vd nhân vật nhảy cao hơn, rơi chậm hơn, tốc độ nhanh hơn v.v).

  - Kinh nghiệm rút ra:
    * Từ ý tưởng đi tới thực tế là một con đường không tưởng.
    * Việc viết code không khó bằng fix bug.
    * Sử dụng kỹ thuật hướng đối tượng sẽ giúp việc quản lý trở nên dễ dàng hơn rất nhiều.
    * Google là một công cụ hỗ trợ đắc lực trong quá trình viết code.
    * Lập trình nói chung cũng khá vui.
