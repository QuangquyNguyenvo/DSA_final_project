# BÁO CÁO TIẾN ĐỘ (Tuần 1)

**Môn học:** Cấu trúc dữ liệu và Giải thuật.

**Mã lớp học phần:** DASA230179_Dot1, HK1 2026–2027.

**Giảng viên hướng dẫn:** Huỳnh Xuân Phụng.

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
![Ảnh kế hoạch được viết tay trên Scrble sau khi thảo luận](img/Planning.png)
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
| 6 | 3 2 1 | Không tìm thấy | — | — | Dừng (dãy đã giảm dần) |

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

| Thành viên | Công việc tuần 1 |
|---|---|
| Nguyễn Võ Quang Quý | - Khởi tạo GitHub repository.<br>- Cài đặt Algorithm L bằng C++.<br>- Cài đặt thuật toán sinh tổ hợp bằng C++.<br>- Dựng khung báo cáo. |
| Đào Nghiêm Minh | - Viết chú thích cho mã nguồn.<br>- Hoàn thiện báo cáo.<br>- Chụp ảnh minh họa test case. |
| Cả nhóm | - Phân tích đề.<br>- Lập kế hoạch.<br>- Kiểm tra chéo mã nguồn và nội dung báo cáo của nhau. |

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

![Kết quả chạy thuật toán hoán vị](img/image.png)

*Hình 1. Kết quả chạy thuật toán hoán vị (n = 3, mảng {1, 2, 3}).*

![Kết quả chạy thuật toán tổ hợp](img/image-1.png)

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

---
# BÁO CÁO TIẾN ĐỘ (Tuần 2): Sinh tập con bằng Gray Code

**Môn học:** Cấu trúc dữ liệu và Giải thuật.

**Mã lớp học phần:** DASA230179_Dot1, HK1 2026–2027.

**Giảng viên hướng dẫn:** Huỳnh Xuân Phụng.

**GitHub Repository:** https://github.com/QuangquyNguyenvo/DSA_final_project

## 1. Tổng quan

### 1.1. Sinh tập con bằng Gray Code (Subset Generation via Gray Code)

Tiếp nối hai thuật toán Algorithm L và Lexicographic Combination đã triển khai trong tuần 1, nhóm tiếp tục nghiên cứu thuật toán sinh tập con bằng Gray Code.

Trong tuần 2 này, nhóm tập trung vào việc tìm hiểu nguyên lý hoạt động, review mã nguồn ban đầu, nghiên cứu phương pháp thay thế sử dụng các phép toán bitwise và xây dựng phương án kiểm chứng tính đúng đắn của thuật toán.

Mục tiêu của tuần này:
- Hoàn thiện thuật toán Gray Code Subset Generation.
- Giải thích tính chất hai tập con liên tiếp khác nhau đúng một phần tử.
- Phân tích và cải thiện cách biểu diễn trạng thái.
- Xây dựng test case kiểm chứng kết quả.
- Kiểm thử chéo và tích hợp thuật toán.

**Minh chứng:**
![Kế hoạch tuần 2 và tuần 3 được viết tay trên Scrble](img/week_2_planning.png)

## 2. Công việc thực hiện

### 2.1. Nghiên cứu Gray Code

Gray Code là một phương pháp mã hoá nhị phân mà hai trạng thái liên tiếp khác nhau đúng một bit. Khác với hệ nhị phân thông thường, Gray Code ưu tiên thay đổi tối thiểu giữa các trạng thái thay vì sắp xếp mã theo thứ tự tăng dần. Đối với bài toán sinh tập con, mỗi bit đại diện cho trạng thái được chọn hoặc không được chọn của một phần tử. Vì vậy việc thay đổi một bit tương đương với việc thao tác thêm hoặc loại bỏ đúng một phần tử khỏi tập con hiện tại.

Với n phần tử, chương trình cần sinh đủ $2^n$ tập con khác nhau. Ví dụ với n = 3:

| i | Nhị phân thường của i | i >> 1 | Mã Gray G(i) | Thao tác |
|---|---|---|---|---|
| 0 | 000 | 000 | 000 | Khởi tạo (tập rỗng) |
| 1 | 001 | 000 | 001 | Lật bit 1, thêm phần tử 1 |
| 2 | 010 | 001 | 011 | Lật bit 2, thêm phần tử 2 |
| 3 | 011 | 001 | 010 | Lật bit 1, bớt phần tử 1 |
| 4 | 100 | 010 | 110 | Lật bit 3, thêm phần tử 3 |
| 5 | 101 | 010 | 111 | Lật bit 1, thêm phần tử 1 |
| 6 | 110 | 011 | 101 | Lật bit 2, bớt phần tử 2 |
| 7 | 111 | 011 | 100 | Lật bit 1, bớt phần tử 1 |


### 2.2. Phân tích mã nguồn ban đầu

Phiên bản ban đầu sử dụng một mảng số nguyên để lưu các bit của trạng thái hiện tại và một biến phụ để luân phiên hai trường hợp lựa chọn vị trí cần thay đổi.

#### Thuật toán hoạt động bằng cách:
- Khởi tạo trạng thái gồm n bit 0.
- Sử dụng biến tmp để chuyển đổi luân phiên hai quy tắc.
- Trường hợp 1: lật bit đầu tiên trong mảng.
- Trường hợp 2: tìm bit 1 đầu tiên theo chiều duyệt và lật bit ngay phía sau.
- Kết thúc khi không còn vị trí hợp lệ nào để thay đổi.

> Phương pháp này cập nhật trực tiếp trạng thái hiện tại, mỗi lần chỉ thay đổi một bit.

**Mã nguồn ban đầu:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/36f11ed/comb_gen.cpp#L25-L36

### 2.3. Nghiên cứu phương pháp Binary Reflected Gray Code

Sau khi phân tích phiên bản ban đầu, nhóm nghiên cứu thêm phương pháp Binary Reflected Gray Code. Phương pháp này có thể tính trực tiếp mã Gray dựa trên chỉ số nhị phân bằng công thức:

 G(i) = i ^ (i>>1)

Trong đó:
- `i` : chỉ số của cấu hình cần sinh
- `>>1` : dịch bit sang phải một vị trí
- `^` : Phép XOR giữa các bit tương ứng.

> Công thức có thể hiểu thông qua quy tắc giữ nguyên bit đầu tiên, sau đó xác định các bit Gray còn lại bằng phép XOR giữa hai bit nhị phân kề nhau. Vì vậy, chương trình có thể tính trực tiếp mã Gray từ chỉ số i mà không cần duy trì mảng trạng thái của mã trước đó.

**Mã nguồn cải tiến:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/030871b/comb_gen.cpp#L38-L48

Ví dụ tính bộ nhớ với n = 10 (dùng cho bảng so sánh bên dưới):
- Ta có 1 byte = 8 bit và mỗi phần tử int tốn 4 byte tương đương 32 bit.
- Với mảng gồm 10 phần tử int thì sẽ tốn 40 byte tương đương 320 bit.

| Tiêu chí | Phiên bản ban đầu | Phương pháp Binary Reflected Gray Code |
|---|---|---|
| Biểu diễn dưới dạng | Mảng `vector<int>` gồm n phần tử, mỗi phần tử lưu một bit 0 hoặc 1 | Một số nguyên, mỗi bit của số đại diện cho một phần tử |
| Phương pháp | Sinh tuần tự từ trạng thái trước, dùng biến `tmp` (parity) để luân phiên hai quy tắc lật bit | Tính trực tiếp mã Gray thứ i bằng công thức `i ^ (i >> 1)` |
| Bộ nhớ | n × 4 byte (n = 10 thì tốn 40 byte) | 4 byte cố định cho một biến int |
| Worst-case (mỗi bước sinh) | O(n) do phải quét mảng để tìm bit 1 đầu tiên | O(1) cho việc tính mã (chưa tính thời gian in ra) |
| Khả năng mở rộng | Không bị giới hạn bởi độ rộng số nguyên, n chỉ phụ thuộc bộ nhớ | Bị giới hạn bởi độ rộng kiểu dữ liệu: int an toàn với n ≤ 30, dùng `long long` thì tối đa khoảng n ≤ 62 |


> Như vậy phương pháp XOR có lợi thế về cách biểu diễn dữ liệu và không cần quét mảng để tìm vị trí cần thay đổi. Tuy nhiên cái gì cũng có trade-off của nó, phương pháp ban đầu vẫn có ưu điểm khi cần xử lý các cấu hình có độ dài bit lớn hơn độ rộng của một số nguyên.

Việc so sánh tốc độ thực thi sẽ được thực hiện ở giai đoạn đánh giá hiệu năng.

## 3. Kiểm thử và kiểm chứng

### 3.1. Phương pháp kiểm chứng

Để đánh giá tính đúng đắn của thuật toán Gray Code, nhóm sử dụng các tiêu chí:

1. Mỗi mã phải nằm trong phạm vi biểu diễn của n bit.
2. Không có hai trạng thái bị trùng lặp.
3. Hai trạng thái liên tiếp phải khác nhau đúng 1 bit.
4. Tổng số mã sinh ra phải bằng $2^n$.

Điều kiện kiểm tra bằng phép XOR giữa trạng thái hiện tại và trạng thái trước đó. Nếu số lượng bit 1 trong kết quả XOR bằng đúng 1 thì bước chuyển thoả mãn tính chất Gray Code. Hàm `verifyGray()` được gọi cho từng mã ngay khi `graycode()` sinh ra và nhận đúng giá trị đã in, nên không tự sinh lại mã bằng công thức. Ba tiêu chí đầu được kiểm tra ở mỗi bước, tiêu chí 4 được kiểm tra khi kết thúc vòng lặp.

**Mã nguồn hàm verify:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/8494cf2/comb_gen.cpp#L37-L76

### 3.2. Các trường hợp kiểm thử


| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|-----|-----|---|---|---|
| TC01 | Biên n = 0 | n = 0 | 2^0 = 1 tập con (tập rỗng) | Sinh 1 tập con, `Tong so ma Gray: 1`, verify đúng | PASS |
| TC02 | n nhỏ nhất có phần tử | n = 1 | 2 mã: 0, 1 (tập rỗng và tập {1}) | Sinh `{ 0 }`, `{ 1 }`, `Tong so ma Gray: 2`, verify đúng | PASS |
| TC03 | Cơ bản | n = 2 | 4 mã: 00, 01, 11, 10 | Sinh đúng thứ tự 00, 01, 11, 10, `Tong so ma Gray: 4` | PASS |
| TC04 | Cơ bản (đối chiếu trace tay) | n = 3 | 8 mã: 000, 001, 011, 010, 110, 111, 101, 100 | Sinh đúng 8 mã, khớp với bảng trace tay ở mục 2.1 | PASS |
| TC05 | Kiểm tra tính phản xạ | n = 4 | 16 mã, nửa sau là nửa đầu đảo ngược và thêm bit 1 ở đầu | Sinh đúng 16 mã, mã thứ 8 là 0100 và mã thứ 9 là 1100 | PASS |
| TC06 | Kích thước trung bình | n = 10 | 2^10 = 1024 mã, các mã liên tiếp khác nhau đúng 1 bit | `Tong so ma Gray: 1024`, `Kiem tra Gray Code: DUNG` | PASS |
| TC07 | Kích thước lớn | n = 20 | 2^20 = 1 048 576 mã | `Tong so ma Gray: 1048576`, `Kiem tra Gray Code: DUNG` | PASS |
| TC08 | Dữ liệu không hợp lệ (âm) | n = -1 | Báo lỗi và quay lại menu | Báo `Loi: n phai thoa 0 <= n <= 30` và quay lại menu | PASS |
| TC09 | Vượt giới hạn int | n = 31 | Báo lỗi và quay lại menu | Báo `Loi: n phai thoa 0 <= n <= 30` và quay lại menu | PASS |

> Ở lần kiểm thử đầu tiên, TC08 và TC09 bị FAIL do chương trình crash (`std::bad_alloc`). Sau khi bổ sung kiểm tra đầu vào (xem mục 6), cả hai trường hợp đều PASS.


### 3.3. Giải thích tính chất Single-bit Difference

Hai mã Gray liên tiếp luôn khác nhau đúng một bit, tức là mỗi bước chỉ thêm hoặc bớt đúng một phần tử khỏi tập con hiện tại.

Xét hai chỉ số liên tiếp i và i + 1, gọi k là số bit 1 liên tiếp ở cuối của i. Khi cộng 1, k bit 1 này chuyển thành 0 và bit 0 ngay trước đó chuyển thành 1, nên `i ^ (i+1)` là một dãy (k+1) bit 1 liên tiếp ở cuối. Khi đó:

 G(i) ^ G(i+1) = (i ^ (i+1)) ^ ((i ^ (i+1)) >> 1)

Hai dãy bit 1 này lệch nhau một vị trí nên triệt tiêu nhau, chỉ còn lại đúng một bit 1.

Ví dụ với i = 3, i + 1 = 4:
- i ^ (i+1) = 011 ^ 100 = 111
- 111 ^ (111 >> 1) = 111 ^ 011 = 100, chỉ khác đúng một bit.
- Kiểm tra: G(3) = 010, G(4) = 110.

Đây cũng chính là điều kiện mà hàm `verifyGray()` kiểm tra bằng `__builtin_popcount(diff) == 1`.

### 3.4. Kiểm tra số lượng cấu hình với n ≥ 10

Theo yêu cầu đề bài, nhóm kiểm tra tổng số cấu hình của cả ba thuật toán với n ≥ 10 và đối chiếu với công thức lý thuyết.

| Mã | Thuật toán | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC10 | Hoán vị | n = 10, mảng {1, 2, ..., 10} | 10! = 3 628 800 | `Tong so hoan vi: 3628800` | PASS |
| TC11 | Tổ hợp | n = 10, k = 5 | C(10, 5) = 252 | `Tong so to hop: 252` | PASS |
| TC12 | Tổ hợp | n = 20, k = 10 | C(20, 10) = 184 756 | `Tong so to hop: 184756` | PASS |
| TC13 | Tổ hợp, biên k = 0 | n = 10, k = 0 | C(10, 0) = 1 (tập rỗng) | `Tong so to hop: 1` | PASS |
| TC14 | Gray Code | n = 10 | 2^10 = 1 024 | `Tong so ma Gray: 1024` (xem TC06) | PASS |
| TC15 | Hoán vị, toàn phần tử trùng | n = 4, mảng {2, 2, 2, 2} | 1 hoán vị duy nhất | `Tong so hoan vi: 1` | PASS |

> TC15 là edge case "all-duplicate values" mà đề bài nêu. Algorithm L dùng so sánh `>=` khi tìm pivot nên tự bỏ qua các hoán vị trùng nhau và chỉ sinh đúng một cấu hình.

### 3.5. Trace tay Gray Code n = 4 và đối chiếu output

Theo góp ý của thầy ở tuần 1, nhóm trace tay trường hợp n = 4 bằng công thức `G(i) = i ^ (i >> 1)` rồi đối chiếu với output của chương trình.

![Bảng trace tay Gray Code với n = 4](img/week_2_trace_gray_n4.png)

*Hình 3. Bảng trace tay Gray Code với n = 4.*

![Output chương trình khi chọn menu 3 với n = 4](img/week_2_output_gray_n4.png)

*Hình 4. Output của chương trình khi chọn menu 3 với n = 4.*

Kết quả: cả 16 mã trong bảng trace tay trùng khớp với output theo đúng thứ tự. Từ bảng trên có thể thấy thêm hai tính chất:
- Tính phản xạ: 8 mã cuối (i = 8 đến 15) là 8 mã đầu đọc ngược và thêm bit 1 ở đầu.
- Tần suất lật bit: trong 15 bước chuyển, bit 1 bị lật 8 lần, bit 2 lật 4 lần, bit 3 lật 2 lần và bit 4 lật 1 lần. Nhận xét này sẽ được dùng cho phần phân tích độ phức tạp khấu hao ở tuần 3.

## 4. Tích hợp và quản lý mã nguồn

Nhóm tiếp tục quản lý mã nguồn bằng GitHub theo quy trình: mỗi thành viên làm việc trên nhánh riêng, tạo Pull Request, thành viên còn lại review rồi mới merge vào nhánh `main`. Nhờ vậy mọi thay đổi đều được kiểm tra chéo trước khi tích hợp và lịch sử phát triển được lưu lại rõ ràng.

**Mã nguồn Gray Code:**
- Phiên bản ban đầu (`legacyNextGray`), cập nhật trực tiếp mảng trạng thái: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/030871b/comb_gen.cpp#L25-L36

- Phiên bản cải tiến (`graycode`), tính trực tiếp bằng `G(i) = i ^ (i >> 1)`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/030871b/comb_gen.cpp#L38-L48


**Mã nguồn Verify:**
- Hàm `verifyGray()` kiểm tra phạm vi, trùng lặp, khác đúng 1 bit và tổng số mã bằng 2^n:
  - Phiên bản đầu (sinh lại mã bằng công thức): https://github.com/QuangquyNguyenvo/DSA_final_project/blob/030871b/comb_gen.cpp#L50-L76
  - Phiên bản sau khi sửa (kiểm tra trực tiếp từng mã `graycode()` sinh ra): https://github.com/QuangquyNguyenvo/DSA_final_project/blob/8494cf2/comb_gen.cpp#L37-L76

**Pull Request:**
- PR #3 (`week2`, Đào Nghiêm Minh): triển khai Gray Code phiên bản ban đầu và khung README tuần 2: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/3

- PR #4 (`feature/graycode`, Nguyễn Võ Quang Quý): cải tiến Gray Code bằng bitwise, thêm hàm verify và bổ sung báo cáo: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/4

- PR #5 (`week2`, Đào Nghiêm Minh): chỉnh sửa README tuần 2 và thêm bảng hand trace: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/5

**Commit:**
- [`36f11ed`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/36f11ed): thêm phần Gray Code và README mới (Minh).
- [`9f53273`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/9f53273): tối ưu sinh Gray Code bằng thao tác bitwise (Quý).
- [`b2bf47f`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/b2bf47f): bổ sung README báo cáo tuần 2 (Quý).
- [`030871b`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/030871b): merge PR #4, tích hợp Gray Code.
- [`4f30369`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/4f30369): sửa README tuần 2, thêm bảng hand trace (Minh).
- [`3d30835`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/3d30835): chặn n không hợp lệ ở menu Gray Code (Quý).
- [`945b627`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/945b627): đổi tên hàm sang tiếng Anh, thống nhất thông báo và sửa chính tả menu (Quý).
- [`8494cf2`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/8494cf2): cho `verifyGray()` kiểm tra trực tiếp từng mã mà `graycode()` sinh ra (Quý).

Theo góp ý của thầy ở tuần 1, nhóm thống nhất từ nay đặt message commit theo dạng `loại: mô tả ngắn`, trong đó `feat:` cho tính năng mới, `fix:` cho sửa lỗi, `docs:` cho báo cáo và README, `refactor:` cho chỉnh sửa mã nguồn không làm thay đổi chức năng.

Sau tuần 2, chương trình `comb_gen.cpp` đã tích hợp ba thuật toán trong cùng một menu: sinh hoán vị (Algorithm L), sinh tổ hợp chập k của n và sinh tập con bằng Gray Code. Lựa chọn Gray Code tự động đưa từng mã vừa sinh qua `verifyGray()` để kiểm chứng.


## 5. Phân công công việc

| Thành viên | Công việc tuần 2 |
|---|---|
| Đào Nghiêm Minh | - Tìm hiểu và triển khai Gray Code phiên bản ban đầu.<br>- Hỗ trợ kiểm thử các test case.<br>- Tích hợp chương trình.<br>- Viết và tổng hợp báo cáo. |
| Nguyễn Võ Quang Quý | - Review mã nguồn.<br>- Nghiên cứu phương pháp XOR.<br>- Phân tích thiết kế.<br>- Cải tiến mã nguồn.<br>- Xây dựng hàm kiểm thử.<br>- Viết và tổng hợp báo cáo. |
| Cả nhóm | - Kiểm tra chéo mã nguồn và báo cáo.<br>- Nộp bài. |


## 6. Khó khăn và hướng giải quyết

- Hiểu quy tắc luân phiên của phiên bản ban đầu: khó giải thích vì sao biến `tmp` luân phiên hai quy tắc lật bit lại sinh đúng thứ tự Gray. Nhóm giải quyết bằng cách trace tay với n = 3 và n = 4.
- Thống nhất thứ tự bit: bản ban đầu lưu `a[0]` là bit thấp nhất, còn `graycode()` in từ bit cao xuống nên kết quả trông như bị đảo ngược. Nhóm thống nhất bit 1 là bit ngoài cùng bên phải.
- Đầu vào không hợp lệ: n = -1 và n = 31 làm chương trình crash do `1 << n` không hợp lệ hoặc tràn `int`. Nhóm đã bổ sung kiểm tra 0 ≤ n ≤ 30 ở menu Gray Code.
- Xuất dữ liệu lớn: n = 20 in hơn một triệu dòng nên rất chậm. Nhóm tạm kiểm tra qua dòng tổng số mã và kết quả `verifyGray()`, tuần 3 sẽ bổ sung giới hạn số cấu hình được in.
- Hàm kiểm chứng chưa độc lập: phiên bản đầu của `verifyGray()` sinh lại mã bằng cùng công thức với hàm sinh nên không kiểm tra được output thật. Nhóm đã sửa để `graycode()` đưa từng mã vừa sinh vào `verifyGray()`. Khi thử cố tình đổi công thức sinh thành `gray = i`, chương trình báo `Kiem tra Gray Code: SAI`.

## 7. Kế hoạch tuần 3
- Hoàn thiện CLI theo yêu cầu đề bài.
- Hỗ trợ in giới hạn số cấu hình đầu tiên.
- Phân tích worst-case, amortized complexity (phân tích khấu hao) và tổng thời gian sinh.
- Benchmark và so sánh hiệu năng.
- Hoàn thiện báo cáo kỹ thuật và Self-Explanation.
- Chuẩn bị cho phần vấn đáp đề tài.

## 8. Khai báo sử dụng AI
nhóm không dùng AI và có quay lại bằng chứng rõ ràng y như tuần 1.

Video minh chứng quá trình tự nghiên cứu và viết mã nguồn tuần 2 của Quý: https://drive.google.com/file/d/1zdsthhp6V-TzWV5NbmcEFX3qUSoUhG5G/view

Video minh chứng tuần 2 của Minh: https://drive.google.com/file/d/1R3uiYg4pMr_WFpjEqWWMRmxVvOA08siG/view


