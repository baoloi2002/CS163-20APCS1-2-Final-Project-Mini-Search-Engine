# CS163-20APCS1-2-Final Project-Mini Search Engine
 Lưu ý: vì 1 số lỗi không xác định được, khi chạy pj vui lòng chạy ở dạng debug(F8) nếu dùng codeblock. Còn lại thì bug ráng chịu
 
 Theo tình hình thì các nhóm khác sử dụng rất nhiều thư viện có sẵn còn nhóm mình thì ... :v nên ai muốn dùng gì để sửa thì dùng. (Hy vọng có ai đó đọc cái này :'( )

 Project được chia làm 4 phần chính:
 - Đọc query được nhập vào.
 - Phân loại Query
 - Thực hiện các tác vụ

# Phần nhập query vào
  Các file có liên quan:
  - "readQuery.h" : các việc chính của việc đọc, in gợi ý
  - "dataQuery.h" : Trie + hashTable
  - "WordToWord.h": như cái tên
  
 Xử lý gợi ý ký tự dựa vào lịch sử người dùng gồm 2 phần:
 1. Gợi ý từ những ký tự ra từ hoàn chỉnh (vd: str -> string, ch -> char)
   - Sử dụng trie kết hợp với hash table
   - Trie sẽ giúp tìm kiếm từ tiền tố ra nguyên kí tự với độ phức tạp O( độ dài ký tự)
   - Ở các nút của Trie ngoài trừ những thông tin thông thường sẽ còn lưu 1 cặp số (hashKey, số lần xuất hiện)
   - Trie sẽ lưu top 5 hashKey xuất hiện nhiều nhất. 
   - Tại mỗi nút của Trie sẽ được kế thừa top kết quả của những nút con của nó và lựa ra top 5

   - Hash table "CountWord.dat" sẽ lưu số lần xuất hiện của các từ được thêm vào.
   - Với 1 file "Words.txt" lưu thứ tự xuất hiện các từ khác nhau đôi 1 thì nếu hash theo đúng thứ tự file thì hashKey của mỗi từ được thêm mới là như nhau
   - Sử dụng hash Table nhằm tối ưu thời gian và bộ nhớ không phải lưu tất cả thông tin lên trie và mỗi lần update chỉ cần update thêm từ mới vào "Words.txt", tăng biến đếm trong hash table và gọi kết quả ra thêm vào trie để tiết kiệm không gian
   - Kích thước hash Table là 10^6 nếu mỗi giây nhập được 1 từ thì phải mất 10 ngày nhập liên tục mới dùng hết lượng vùng nhớ này. Và vì thông tin lưu chỉ có lịch sử người dùng nên cấu trúc này là tiện lợi đủ nhanh và đủ lớn để lưu

 2. Gợi ý Word to Word (vd: to -> school, eat -> breakfast)
   - Phần này vì tôi lưu trực tiếp ra file trong thư mục "WordToWordData" 
   - Với những từ mới chỉ cần chạy insertSort vào file đã có hoặc nếu chưa thì tạo file mới
   - Nếu cần gợi ý ký tự thì giả sử ký tự cuối cùng là "to" chương trình sẽ mở file "to.txt" để lấy thông tin ra và gợi ý top 5

 Sau khi query được nhập hoàn tất và người dùng "Enter" thì chuỗi sẽ được phân tách để lưu vào các data structure ở trên. Việc lưu này sẽ tốn chi phí = độ dài query + việc lưu cả file hashTable lại.
 
 # Phân loại Query
   Các file có liên quan: 
   - "typeOfQuestion.h" : như cai tên
   
   Chỉ đơn giản là duyệt qua hết query và tìm ra những điểm đáng chú ý để phân loại
   
 # Thực hiện các tác vụ
   Các file có liên quan:
   - "MainDataBuild.h"  : Lưu cấu trúc chính Trie, Avl Tree
   - "AVL_in_AVL.h"     : Cấu trúc cây AVL với key là số và lưu thông tin của 1 AVL khác ở mỗi nút
   - "AvlTree.h"        : Cấu trúc cây AVL với key là tên file và lưu số lần 1 từ xuất hiện trong file đó
   - "removeStopWords.h": Cấu trúc Trie lưu những stop word cần bị loại bỏ
   - "Synonym.h"        : Cấu trúc cây AVL với key là hashkey của word và lưu danh sách từ đồng nghĩa
   
   Data xử lý theo các bước sau:
   1. Lấy danh sách những file có ký tự hợp lệ, bỏ đi những file còn lại
   2. Lấy từng từ trong file để add vao TrieAVL. Loại bỏ những stopWord vì stopWord đã bị bỏ khỏi query nên không có giá trị sử dụng
   3. Lưu Data cho những trường hợp đặc biệt như price hay hashTag
   
   Cấu trúc chung:
   1. Tách chuỗi ban đầu thành các chuỗi con
   2. Chuẩn hóa các chuỗi con và loại bỏ những từ là stop word
   3. Tìm kiếm tập hợp những file có sự xuất hiện của những từ trên
   4. Chọn ra top 5 file và duyệt lãi những file đó đánh dâu vị trí xuất hiện và in ra màn hình

  Việc dùng Trie sẽ giúp tìm kiếm dễ dàng và thuận tiện cho việc update thêm thông tin sau này mà không cần phải dừng chương trình hay nới rộng giới như với hash Table
  
  Avl tree giúp việc cập nhật số lần xuất hiện dễ dàng và có thự tự với key là number. Thuận tiện cho việc update thêm thông tin sau này mà không cần phải dừng chương trình hay nới rộng giới như với hash Table
  
  Những query cụ thể:
  
  AND                : lấy kết quả tìm được và tìm phần giao của kết quả
  
  OR                 : lấy như bình thường
  
  Manchester –united : Lấy kết quả như bình thường cho phần âm và phân dương. Rồi loại bỏ nhưng kết quả là phần giao của phần âm và dương ra khỏi phần dương
  
  intitle:bamboo     : lấy như bình thường. Tăng điểm ưu tiên cho những file có các ký tự đầu trùng với query
  
  Butter +and Jam    : Làm như phép AND
  
  filetype:txt       : Truy cập vào danh sách tên file và tìm những file có đuôi giống vậy
  
  Search for a price : Dùng cấu trúc AVL in AVL để tìm kiếm price. Những data về price được lưu ra file riêng
  
  Search hashtags    : Dùng 1 Trie khác lưu Data cho hashTag và tìm như bình thường
  
  Exact match        : Làm như phép AND và chạy O(NxM) để tìm sequence hợp lệ từ top kq
  
  Wildcard           : Tách các chuỗi tại vị trí dấu sao và làm như Exact Match
  
  Range of numbers   : Với thiết kế cấu trúc AVL in AVL có thể dễ dàng tìm được trong khoảng mà không cần phải tìm kiểm tất cả kq. Chỉ cần duyệt trên cây AVL với 2 biến L, R để kiểm tra đúng vị trí
  
  Synonym            : Lấy danh sách những synonym của từ đó và tìm kiếm như bình thường
  
