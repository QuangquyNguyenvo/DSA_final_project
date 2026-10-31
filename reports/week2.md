# BÁO CÁO TIẾN ĐỘ (Tuần 2): Sinh tập con bằng Gray Code

**Môn học:** Cấu trúc dữ liệu và Giải thuật.

**Mã lớp học phần:** DASA230179_Dot1, HK1 2026-2027.

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
![Kế hoạch tuần 2 và tuần 3 được viết tay trên Scrble](../img/week_2_planning.png)

## 2. Công việc thực hiện

### 2.1. Nghiên cứu Gray Code

Gray Code là một phương pháp mã hoá nhị phân mà hai trạng thái liên tiếp khác nhau đúng một bit. Khác với hệ nhị phân thông thường, Gray Code ưu tiên thay đổi tối thiểu giữa các trạng thái thay vì sắp xếp mã theo thứ tự tăng dần. Đối với bài toán sinh tập con, mỗi bit đại diện cho trạng thái được chọn hoặc không được chọn của một phần tử. Vì vậy việc thay đổi một bit tương đương với việc thao tác thêm hoặc loại bỏ đúng một phần tử khỏi tập con hiện tại. [1], [4]

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

Sau khi phân tích phiên bản ban đầu, nhóm nghiên cứu thêm phương pháp Binary Reflected Gray Code. Phương pháp này có thể tính trực tiếp mã Gray dựa trên chỉ số nhị phân bằng công thức [3], [4]:

 G(i) = i ^ (i>>1)

Trong đó (các phép toán bit tham khảo từ [2], [5]):
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

![Bảng trace tay Gray Code với n = 4](../img/week_2_trace_gray_n4.png)

*Hình 3. Bảng trace tay Gray Code với n = 4.*

![Output chương trình khi chọn menu 3 với n = 4](../img/week_2_output_gray_n4.png)

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
- PR #3 (`week2`, Đào Nghiệm Minh): triển khai Gray Code phiên bản ban đầu và khung README tuần 2: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/3

- PR #4 (`feature/graycode`, Nguyễn Võ Quang Quý): cải tiến Gray Code bằng bitwise, thêm hàm verify và bổ sung báo cáo: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/4

- PR #5 (`week2`, Đào Nghiệm Minh): chỉnh sửa README tuần 2 và thêm bảng hand trace: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/5

- PR #6 (`feature/graycode`, Nguyễn Võ Quang Quý): chặn đầu vào không hợp lệ, cho `verifyGray()` kiểm tra trực tiếp output, thống nhất thông báo, bổ sung test n ≥ 10 và trace tay n = 4: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/6

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

| Thành viên | MSSV | Công việc tuần 2 |
|---|---|---|
| Đào Nghiệm Minh | 25110042 | - Tìm hiểu và triển khai Gray Code phiên bản ban đầu.<br>- Hỗ trợ kiểm thử các test case.<br>- Tích hợp chương trình.<br>- Viết và tổng hợp báo cáo. |
| Nguyễn Võ Quang Quý | 25110055 | - Review mã nguồn.<br>- Nghiên cứu phương pháp XOR.<br>- Phân tích thiết kế.<br>- Cải tiến mã nguồn.<br>- Xây dựng hàm kiểm thử.<br>- Viết và tổng hợp báo cáo. |
| Cả nhóm | | - Kiểm tra chéo mã nguồn và báo cáo.<br>- Nộp bài. |


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

## 8. Khai báo sử dụng AI và nguồn tài liệu tham khảo

### 8.1. Khai báo sử dụng AI và nguồn gốc kiến thức

Nhóm không sử dụng công cụ AI trong quá trình nghiên cứu, viết mã nguồn và viết báo cáo. Tương tự tuần 1, nhóm chỉ sử dụng Search Engine của Google để tìm kiếm và tra cứu tài liệu, từ đó tìm được các nguồn tham khảo được liệt kê ở mục 8.2. Toàn bộ quá trình thực hiện được quay video minh chứng (xem bên dưới). Các kiến thức sử dụng trong báo cáo đến từ những nguồn sau, và được đánh dấu [1]-[5] tại vị trí sử dụng trong báo cáo, tương ứng với danh sách ở mục 8.2.

Các kiến thức nền tảng về Gray Code, biểu diễn nhị phân và tính chất thay đổi một bit giữa hai trạng thái liên tiếp đã được nhóm tiếp cận trong học phần Toán rời rạc và Lý thuyết đồ thị, đặc biệt thông qua nội dung Boolean Algebra và Karnaugh Map (K-map).

Các thao tác bitwise như XOR, AND, OR và dịch bit cũng là những kiến thức lập trình đã được tiếp cận từ trước và tiếp tục được sử dụng trong quá trình luyện tập lập trình thi đấu, bao gồm ôn tập ICPC tại trường.

**Video minh chứng quá trình thực hiện tuần 2**

- **Nguyễn Võ Quang Quý:** [Xem video](https://drive.google.com/file/d/1zdsthhp6V-TzWV5NbmcEFX3qUSoUhG5G/view)
- **Đào Nghiệm Minh:** [Xem video](https://drive.google.com/file/d/1R3uiYg4pMr_WFpjEqWWMRmxVvOA08siG/view)

### 8.2. Tài liệu tham khảo

**[1] Học phần Toán rời rạc và Lý thuyết đồ thị (Discrete Mathematics and Graph Theory)**

Trường Đại học Công nghệ Kỹ thuật TP.HCM (HCMUTE).

Nội dung liên quan: Boolean Algebra, Karnaugh Map (K-map), biểu diễn nhị phân và các tính chất của Gray Code.

**[2] VNOI Wiki: Phép toán bit**

[https://wiki.vnoi.info/algo/basic/bitwise-operators](https://wiki.vnoi.info/algo/basic/bitwise-operators)

Nội dung liên quan: Các toán tử bitwise, XOR, phép dịch bit và ứng dụng trong lập trình.

**[3] GeeksforGeeks: Generate n-bit Gray Codes**

[https://www.geeksforgeeks.org/dsa/generate-n-bit-gray-codes/](https://www.geeksforgeeks.org/dsa/generate-n-bit-gray-codes/)

Nội dung liên quan: Các phương pháp sinh Gray Code, công thức `G(i) = i ^ (i >> 1)` và ví dụ sinh mã Gray bằng thao tác bitwise.

**[4] CP-Algorithms: Gray Code**

[https://cp-algorithms.com/algebra/gray-code.html](https://cp-algorithms.com/algebra/gray-code.html)

Nội dung liên quan: Binary Reflected Gray Code, công thức chuyển đổi giữa mã nhị phân và mã Gray, cùng các tính chất của dãy Gray Code.

**[5] Viblo: Thao tác xử lý bit và ứng dụng (Bit Manipulation)**

[https://viblo.asia/p/thao-tac-xu-ly-bit-va-ung-dung-bit-manipulation-3kY4gxl9JAe](https://viblo.asia/p/thao-tac-xu-ly-bit-va-ung-dung-bit-manipulation-3kY4gxl9JAe)

Nội dung liên quan: Các thao tác xử lý bit và ứng dụng trong lập trình.

