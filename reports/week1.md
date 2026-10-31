# BÁO CÁO TIẾN ĐỘ (Tuần 1)

**Môn học:** Cấu trúc dữ liệu và Giải thuật.

**Mã lớp học phần:** DASA230179_Dot1, HK1 2026-2027.

**Giảng viên hướng dẫn:** Huỳnh Xuân Phụng.

**Thành viên nhóm:**

| Họ và tên | MSSV |
|---|---|
| Nguyễn Võ Quang Quý | 25110055 |
| Đào Nghiệm Minh | 25110042 |

**GitHub Repository:** https://github.com/QuangquyNguyenvo/DSA_final_project

## 1. Tổng quan

Sau khi rà soát quá trình thực hiện ban đầu, nhóm nhận thấy việc nghiên cứu và kiểm chứng các thuật toán chưa được thực hiện đủ kỹ lưỡng. Do đó, nhóm quyết định tổ chức lại quá trình triển khai, bắt đầu từ việc phân tích yêu cầu và nghiên cứu nguyên lý hoạt động của từng thuật toán. Trong tuần 1 của kế hoạch điều chỉnh, nhóm tập trung vào hai thuật toán sinh cấu hình theo thứ tự từ điển:

- Algorithm L (Lexicographic Permutation): sinh hoán vị kế tiếp theo thứ tự từ điển.
- Lexicographic Combination: sinh tổ hợp chập k của n theo thứ tự từ điển.

Mục tiêu là cài đặt hai thuật toán, kiểm tra tính đúng đắn trên các ví dụ cơ bản và làm nền tảng cho những giai đoạn tiếp theo.

## 2. Công việc thực hiện
### 2.1. Phân tích đề bài và lập kế hoạch
- Phân tích các yêu cầu chức năng và kỹ thuật của đề tài.
- Tham khảo tài liệu The Art of Computer Programming, Vol. 4A, Chapter 7.2.1 (Generating Combinatorial Patterns).
- Lập kế hoạch triển khai, phương pháp kiểm thử và danh sách sản phẩm cần hoàn thành.
- Chia kế hoạch thực hiện theo từng giai đoạn (3 tuần).
- Khởi tạo GitHub repository để quản lý mã nguồn và theo dõi lịch sử phát triển.

**Minh chứng:** 
![Ảnh kế hoạch được viết tay trên Scrble sau khi thảo luận](../img/Planning.png)
### 2.2. Algorithm L - Lexicographic Permutation
Nghiên cứu và triển khai thuật toán sinh hoán vị kế tiếp theo thứ tự từ điển.

Thuật toán hoạt động bằng cách tìm vị trí ngoài cùng bên phải còn có thể tăng (pivot), lựa chọn phần tử thay thế phù hợp, hoán đổi và đảo đoạn phía sau để tạo hoán vị kế tiếp nhỏ nhất (đúng với thứ tự từ điển).

Nội dung triển khai bao gồm:
- Xác định Pivot và các phần tử kế nhiệm (Successor).
- Hoán đổi và đảo đoạn suffix.
- Xử lý trường hợp không còn hoán vị kế tiếp (dãy đã giảm dần thì dừng).
- In lần lượt các hoán vị ra màn hình, bắt đầu từ cấu hình nhỏ nhất.

**Bảng hand trace:** Ví dụ với n = 3, mảng {1, 2, 3}
| Bước | Hoán vị hiện tại | Pivot (vị trí i) | Successor (vị trí j) | Sau khi hoán đổi | Sau khi đảo suffix |
|---|---|---|---|---|---|
| 1 | 1 2 3 | a[2] = 2 | a[3] = 3 | 1 3 2 | 1 3 2 |
| 2 | 1 3 2 | a[1] = 1 | a[3] = 2 | 2 3 1 | 2 1 3 |
| 3 | 2 1 3 | a[2] = 1 | a[3] = 3 | 2 3 1 | 2 3 1 |
| 4 | 2 3 1 | a[1] = 2 | a[2] = 3 | 3 2 1 | 3 1 2 |
| 5 | 3 1 2 | a[2] = 1 | a[3] = 2 | 3 2 1 | 3 2 1 |
| 6 | 3 2 1 | Không tìm thấy | - | - | Dừng (dãy đã giảm dần) |

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1994c8c/comb_gen.cpp#L4-L15

### 2.3. Lexicographic Combination

Nghiên cứu và triển khai thuật toán sinh tổ hợp chập k của n theo thứ tự từ điển. Mỗi tổ hợp được biểu diễn bằng một dãy tăng dần. Thuật toán tìm vị trí ngoài cùng bên phải chưa đạt giới hạn, tăng phần tử tại vị trí đó và đặt các phần tử phía sau về giá trị nhỏ nhất hợp lệ.

Nội dung triển khai bao gồm:
- Khởi tạo tổ hợp đầu tiên {1, 2, ..., k}.
- Xác định giới hạn tối đa của từng vị trí.
- Sinh tổ hợp kế tiếp theo thứ tự từ điển.
- Xử lý điều kiện dừng và các trường hợp biên (ví dụ k > n).

**Bảng hand trace:**  Ví dụ với n = 5, k = 3

| Bước | Tổ hợp hiện tại | Vị trí cần tăng | Thao tác | Tổ hợp kế tiếp |
|---|---|---|---|---|
| 1 | 1 2 3 | 3 | Tăng 3 lên 4 | 1 2 4 |
| 2 | 1 2 4 | 3 | Tăng 4 lên 5 | 1 2 5 |
| 3 | 1 2 5 | 2 | Tăng 2 lên 3, đặt lại vị trí 3 = 4 | 1 3 4 |
| 4 | 1 3 4 | 3 | Tăng 4 lên 5 | 1 3 5 |
| 5 | 1 3 5 | 2 | Tăng 3 lên 4, đặt lại vị trí 3 = 5 | 1 4 5 |
| 6 | 1 4 5 | 1 | Tăng 1 lên 2, đặt lại thành 3, 4 | 2 3 4 |
| 7 | 2 3 4 | 3 | Tăng 4 lên 5 | 2 3 5 |
| 8 | 2 3 5 | 2 | Tăng 3 lên 4, đặt lại vị trí 3 = 5 | 2 4 5 |
| 9 | 2 4 5 | 1 | Tăng 2 lên 3, đặt lại thành 4, 5 | 3 4 5 |
| 10 | 3 4 5 | Không tìm thấy | Mọi vị trí đều đạt giới hạn | Dừng |

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1994c8c/comb_gen.cpp#L16-L24

### 2.4. Hướng dẫn biên dịch và chạy chương trình

Chương trình được viết bằng C++17, sử dụng trình biên dịch G++.

Biên dịch:

```bash
g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen
```

Chạy trên Windows PowerShell:

```powershell
.\comb_gen.exe
```

Chạy trên Linux:

```bash
./comb_gen
```

Sau khi chạy, chương trình hiển thị menu cho phép lựa chọn thuật toán sinh hoán vị hoặc tổ hợp, nhập dữ liệu đầu vào và xem kết quả theo thứ tự từ điển.

### 2.5. Phân công công việc

| Thành viên | MSSV | Công việc tuần 1 |
|---|---|---|
| Nguyễn Võ Quang Quý | 25110055 | - Khởi tạo GitHub repository.<br>- Cài đặt Algorithm L bằng C++.<br>- Cài đặt thuật toán sinh tổ hợp bằng C++.<br>- Dựng khung báo cáo. |
| Đào Nghiệm Minh | 25110042 | - Viết chú thích cho mã nguồn.<br>- Hoàn thiện báo cáo.<br>- Chụp ảnh minh họa test case. |
| Cả nhóm | | - Phân tích đề.<br>- Lập kế hoạch.<br>- Kiểm tra chéo mã nguồn và nội dung báo cáo của nhau. |

## 3. Kiểm thử và kết quả

### 3.1. Phương pháp kiểm chứng

Để đảm bảo tính đúng đắn của hai thuật toán, nhóm tiến hành kiểm thử dựa trên hai tiêu chuẩn:
1. Tính đúng đắn theo thứ tự từ điển: Cấu hình sau luôn lớn hơn cấu hình trước theo quan hệ thứ tự từ điển và không có cấu hình nào bị lặp lại hoặc bỏ sót.
2. Số lượng cấu hình sinh ra: Tổng số cấu hình chương trình sinh được phải khớp với công thức lý thuyết:
   - Với hoán vị (các phần tử đôi một khác nhau): P(n) = n!
   - Với tổ hợp chập k của n: $C_n^k = \dfrac{n!}{k!(n - k)!}$

### 3.2. Các trường hợp kiểm thử cụ thể (Test Cases)

- Test Case 1 (TC01) - Hoán vị cơ bản (Algorithm L):
  + Dữ liệu đầu vào: n = 3, mảng phần tử {1, 2, 3}.
  + Kết quả kỳ vọng: 3! = 6 hoán vị theo thứ tự từ điển tăng dần.
  + Kết quả thực tế: Sinh đủ 6 hoán vị, bắt đầu từ {1, 2, 3} và dừng tại {3, 2, 1}.
  + Trạng thái: PASS.

- Test Case 2 (TC02) - Hoán vị với mảng ban đầu chưa sắp xếp:
  + Dữ liệu đầu vào: n = 4, mảng phần tử {3, 1, 4, 2}.
  + Kết quả kỳ vọng: Chương trình tự động sắp xếp lại thành {1, 2, 3, 4} rồi sinh đủ 4! = 24 hoán vị.
  + Kết quả thực tế: Sinh chính xác 24 hoán vị theo thứ tự từ điển.
  + Trạng thái: PASS.

- Test Case 3 (TC03) - Tổ hợp chập k của n (Lexicographic Combination):
  + Dữ liệu đầu vào: n = 5, k = 3.
  + Kết quả kỳ vọng: C(5, 3) = 10 tổ hợp từ {1, 2, 3} đến {3, 4, 5}.
  + Kết quả thực tế: Sinh đúng 10 tổ hợp tăng dần nghiêm ngặt.
  + Trạng thái: PASS.

- Test Case 4 (TC04) - Tổ hợp, trường hợp biên k = n:
  + Dữ liệu đầu vào: n = 4, k = 4.
  + Kết quả kỳ vọng: C(4, 4) = 1 tổ hợp duy nhất là {1, 2, 3, 4}.
  + Kết quả thực tế: Sinh đúng 1 cấu hình và dừng lại ngay.
  + Trạng thái: PASS.

- Test Case 5 (TC05) - Tổ hợp, dữ liệu đầu vào không hợp lệ:
  + Dữ liệu đầu vào: n = 3, k = 5 (với k > n).
  + Kết quả kỳ vọng: Báo lỗi dữ liệu không hợp lệ và cho nhập lại, không rơi vào vòng lặp vô hạn.
  + Kết quả thực tế: Chương trình in thông báo lỗi và quay lại menu.
  + Trạng thái: PASS.

### 3.3. Minh họa kết quả thực thi chương trình

![Kết quả chạy thuật toán hoán vị](../img/image.png)

*Hình 1. Kết quả chạy thuật toán hoán vị (n = 3, mảng {1, 2, 3}).*

![Kết quả chạy thuật toán tổ hợp](../img/image-1.png)

*Hình 2. Kết quả chạy thuật toán tổ hợp (n = 5, k = 3).*

## 4. Khó khăn và hướng giải quyết

Trong quá trình nghiên cứu, nhóm cần làm rõ sự khác biệt giữa việc sinh hoán vị và sinh tổ hợp, đặc biệt là cách xác định cấu hình kế tiếp theo thứ tự từ điển.

Đối với Algorithm L, trọng tâm là xác định pivot, chọn phần tử thay thế và hiểu vì sao có thể dùng thao tác đảo ngược (reverse) thay cho việc sắp xếp lại đoạn suffix.

Đối với Lexicographic Combination, trọng tâm là xác định giới hạn của từng vị trí và bảo đảm các phần tử phía sau luôn được đặt lại về giá trị nhỏ nhất hợp lệ.

Vì đây là bài tập nhóm, nhóm không chỉ chia việc cho nhanh mà còn muốn mỗi thành viên đều hiểu bản chất của toàn bộ đề tài, không chỉ riêng phần mình phụ trách. Nhóm trao đổi qua Discord để thống nhất các vấn đề cần giải quyết, quản lý mã nguồn bằng GitHub và kiểm tra chéo phần việc của nhau trước khi tổng hợp.

Nhóm sử dụng các ví dụ giải tay và kết quả chương trình để kiểm tra từng bước của thuật toán. Để ưu tiên việc hiểu rõ thuật toán, nhóm hạn chế tối đa việc sử dụng AI. Điều này khiến nhóm tốn thêm nhiều thời gian tìm hiểu trên các trang web và đọc kỹ tài liệu trước khi bắt đầu làm.

## 5. Kế hoạch tiếp theo

Sau khi báo cáo tuần 1 được duyệt, nhóm dự kiến thực hiện các mục đã lên kế hoạch cho tuần 2:
- Nghiên cứu và triển khai thuật toán sinh tập con bằng Gray Code.
- Giải thích vì sao hai tập con liên tiếp chỉ khác nhau đúng một phần tử.
- Kiểm thử chéo giữa các thành viên trong nhóm.
- Tích hợp ba thuật toán vào cùng một chương trình.

Tiếp theo, nhóm sẽ hoàn thiện CLI, xây dựng bộ kiểm thử tự động và phân tích độ phức tạp thuật toán.

## 6. Tổng kết

Trong tuần 1 của kế hoạch điều chỉnh, nhóm tập trung xây dựng lại thuật toán và tổ chức mã nguồn, triển khai và kiểm chứng đầy đủ hai thuật toán sinh cấu hình theo thứ tự từ điển. Các nội dung này sẽ là cơ sở để nhóm tiếp tục thực hiện Gray Code, tích hợp chương trình và đánh giá kết quả trong những giai đoạn tiếp theo.

## 7. Khai báo sử dụng AI

Trong tuần 1 này nhóm gần như không sử dụng bất kì công cụ LLM nào, chỉ sử dụng Search Engine của Google để nghiên cứu và tìm kiếm giải pháp cho đề bài được đưa ra.

**video minh chứng quá trình thực hiện dự án :** https://drive.google.com/file/d/1eT6iHTBMZKUkUi9EnYQ2bXtV02wnVezB/view?usp=sharing

