# BÁO CÁO DỰ ÁN

**Đề tài:** Combinatorial Generation: Permutations, Combinations, and Subsets

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

Dự án nghiên cứu và triển khai các thuật toán sinh hoán vị, tổ hợp và tập con theo một thứ tự xác định, dựa trên định hướng của The Art of Computer Programming, Vol. 4A, Chapter 7.2.1 — Generating Combinatorial Patterns.

Chương trình được viết bằng C++17, cung cấp giao diện dòng lệnh (CLI), kiểm chứng tính đúng đắn và số lượng cấu hình, đồng thời đo hiệu năng để đối chiếu với phân tích độ phức tạp.

### 1.1. Yêu cầu đề bài

- Cài đặt Algorithm L để sinh hoán vị theo thứ tự từ điển.
- Sinh tổ hợp chập k của n theo thứ tự từ điển.
- Sinh **tập con (subset)** bằng Gray Code; hai tập con liên tiếp khác nhau đúng một phần tử.
- Kiểm chứng số cấu hình với n đến ít nhất 10, đối chiếu n!, C(n, k) và 2ⁿ.
- Giải thích tính chất khác nhau đúng một phần tử của bộ sinh tập con.
- Phân tích thời gian sinh mỗi cấu hình và tổng thời gian sinh.
- Có ví dụ trace tay, dữ liệu lớn và trường hợp biên.
- Cung cấp CLI cho phép in một số cấu hình đầu tiên của cả ba dãy.

### 1.2. Quá trình triển khai

Nhóm bắt đầu từ phân tích đề bài, lập kế hoạch và cài đặt hoán vị, tổ hợp; sau đó bổ sung Gray Code và kiểm chứng. Các giai đoạn tiếp theo gồm tích hợp CLI, phân tích độ phức tạp, xây dựng benchmark, đo lại trong cùng môi trường, vẽ biểu đồ và hoàn thiện chương trình. Phần hiển thị cuối cùng bổ sung tập con bên cạnh chuỗi bit để thể hiện rõ yêu cầu subset generation.

Báo cáo này tổng hợp nội dung từ [README.md](README.md), sử dụng lại các bảng kiểm thử, số liệu và hình minh chứng đã ghi nhận. Các kết quả đó không phải một lần đo mới khi biên soạn tài liệu này.

![Kế hoạch thực hiện dự án](img/Planning.png)

## 2. Công việc thực hiện

### 2.1. Algorithm L - Lexicographic Permutation

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
| 1 | 1 2 3 | a = 2 | a = 3 | 1 3 2 | 1 3 2 |
| 2 | 1 3 2 | a = 1 | a = 2 | 2 3 1 | 2 1 3 |
| 3 | 2 1 3 | a = 1 | a = 3 | 2 3 1 | 2 3 1 |
| 4 | 2 3 1 | a = 2 | a = 3 | 3 2 1 | 3 1 2 |
| 5 | 3 1 2 | a = 1 | a = 2 | 3 2 1 | 3 2 1 |
| 6 | 3 2 1 | Không tìm thấy | - | - | Dừng (dãy đã giảm dần) |

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1994c8c/comb_gen.cpp#L4-L15

### 2.2. Lexicographic Combination

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

### 2.3. Sinh tập con bằng Gray Code

Mỗi tập con của {1, 2, ..., n} được biểu diễn bằng một chuỗi n bit. Bit bằng 1 nghĩa là phần tử tương ứng được chọn. Có 2ⁿ chuỗi bit tương ứng với 2ⁿ tập con, bao gồm tập rỗng.

Chương trình sử dụng Binary Reflected Gray Code:

```cpp
int gray = i ^ (i >> 1);
```

Chỉ số i chạy từ 0 đến 2ⁿ − 1. Mỗi mã được đưa qua `verifyGray()` để kiểm tra phạm vi, phát hiện trùng bằng mảng `seen` và kiểm tra XOR với mã trước có đúng một bit 1. Khi kết thúc, chương trình kiểm tra tổng số mã bằng 2ⁿ. Hàm kiểm chứng nhận đúng giá trị vừa sinh, không tự sinh lại một dãy mã độc lập.

#### Tính chất Single-bit Difference

Hai mã Gray liên tiếp luôn khác nhau đúng một bit, tức là mỗi bước chỉ thêm hoặc bớt đúng một phần tử khỏi tập con hiện tại.

Xét hai chỉ số liên tiếp i và i + 1, gọi k là số bit 1 liên tiếp ở cuối của i. Khi cộng 1, k bit 1 này chuyển thành 0 và bit 0 ngay trước đó chuyển thành 1, nên `i ^ (i+1)` là một dãy (k+1) bit 1 liên tiếp ở cuối. Khi đó:

 G(i) ^ G(i+1) = (i ^ (i+1)) ^ ((i ^ (i+1)) >> 1)

Hai dãy bit 1 này lệch nhau một vị trí nên triệt tiêu nhau, chỉ còn lại đúng một bit 1.

Ví dụ với i = 3, i + 1 = 4:
- i ^ (i+1) = 011 ^ 100 = 111
- 111 ^ (111 >> 1) = 111 ^ 011 = 100, chỉ khác đúng một bit.
- Kiểm tra: G(3) = 010, G(4) = 110.

Đây cũng chính là điều kiện mà hàm `verifyGray()` kiểm tra bằng `__builtin_popcount(diff) == 1`.

#### Hiển thị tập con (subset) bên cạnh mã Gray

Đề bài yêu cầu sinh tập con (subset generation) bằng Gray Code, trong đó hai tập con liên tiếp khác nhau đúng một phần tử. Trước đây, chương trình chỉ in chuỗi bit như `{ 1 1 0 }`. Chuỗi bit đã biểu diễn một tập con, nhưng chưa hiển thị trực tiếp các phần tử được chọn.

Nhóm bổ sung phần in tập con thật của tập {1, 2, ..., n} ngay bên cạnh chuỗi bit. Các bit từ trái sang phải lần lượt ứng với phần tử 1 đến n, bit bằng 1 nghĩa là phần tử đó thuộc tập con. 

Ví dụ với n = 3:

```text
{ 0 0 0 } -> {}
{ 0 0 1 } -> {3}
{ 0 1 1 } -> {2, 3}
{ 0 1 0 } -> {2}
{ 1 1 0 } -> {1, 2}
{ 1 1 1 } -> {1, 2, 3}
{ 1 0 1 } -> {1, 3}
{ 1 0 0 } -> {1}
```

Thay đổi chỉ nằm ở phần in trong `graycode()`: duyệt các bit từ trái sang phải, nếu bit thứ j bằng 1 thì in phần tử `n-j`, dùng biến `first` để ngăn cách các phần tử bằng dấu phẩy. Công thức `i ^ (i >> 1)`, thứ tự mã Gray, giới hạn in và phần kiểm tra `verifyGray()` vẫn giữ nguyên.

Cách hiển thị này làm rõ kết quả subset theo yêu cầu đề bài: người dùng vừa thấy mã bit, vừa thấy tập con tương ứng, và có thể đối chiếu trực tiếp việc mỗi bước chỉ thêm hoặc bỏ đúng một phần tử. Chương trình đã được biên dịch và chạy thử với n = 3 và n = 0 (tập rỗng), phần kiểm tra Gray Code đều trả về đúng.

**Thay đổi so với phiên bản ban đầu:** trước đây, mỗi dòng chỉ có chuỗi bit, ví dụ `{ 1 1 0 }`. Sau khi sửa, dòng kết quả là `{ 1 1 0 } -> {1, 2}`, thể hiện trực tiếp tập con được chọn. Phần bổ sung duyệt các bit từ trái sang phải và in phần tử tương ứng khi bit bằng 1; các vị trí hiển thị lần lượt đại diện cho phần tử 1 đến n. Công thức sinh và thứ tự chuỗi bit giữ nguyên; chỉ bổ sung cách trình bày tập con. Ảnh dưới cho thấy đủ 8 tập con với n = 3, bao gồm tập rỗng, và kết quả kiểm tra Gray Code đúng.

**Minh chứng sau khi sửa:**

![Kết quả Gray Code n = 3: in chuỗi bit và tập con tương ứng](img/graycode_subset_output.png)

### 2.4. Thiết kế CLI và giới hạn số cấu hình được in

Ban đầu chương trình chỉ chặn n để tránh in quá nhiều dòng, nhưng ở giới hạn trên chương trình vẫn in rất nhiều (hoán vị n = 10 ra khoảng 3,6 triệu dòng, Gray Code n = 30 ra hơn 1 tỉ dòng). Trong giai đoạn hoàn thiện, nhóm cho người dùng chọn số cấu hình muốn in ở cả ba menu, theo đúng yêu cầu CLI của đề bài.

**Cách hoạt động:**

- Nhập xong thông số, chương trình hỏi thêm `So cau hinh muon in (0 = tat ca):`.
- Chương trình in tối đa `limit` cấu hình đầu tiên, nếu vẫn còn cấu hình chưa in thì in thêm `...`. Nhập `0` thì in hết như trước.
- Thuật toán vẫn sinh đủ mọi cấu hình, nên `Tong so ...` vẫn là tổng thật và `verifyGray()` vẫn kiểm tra đủ 2ⁿ mã.
- Vì vậy giới hạn in chỉ làm output ngắn lại, thời gian chạy vẫn tăng theo tổng số cấu hình.
- Trong code, giá trị này tên là `limit` để không nhầm với k trong "tổ hợp chập k".

| Lựa chọn | Dữ liệu nhập (theo thứ tự) | Điều kiện của `limit` |
|---|---|---|
| 1. Hoán vị | n, n phần tử, `limit` | `limit` ≥ 0 |
| 2. Tổ hợp | n, k, `limit` | `limit` ≥ 0 |
| 3. Gray Code | n, `limit` | `limit` ≥ 0 |

Giới hạn đầu vào: hoán vị 0 ≤ n ≤ 10; tổ hợp 0 ≤ k ≤ n ≤ 20; Gray Code 0 ≤ n ≤ 30.

**Thay đổi trong mã nguồn:**

- Thêm hàm `readLimit()` để đọc `limit`. Nhập số âm hoặc nhập chữ thì báo lỗi và quay lại menu (xem mục 6).
- Hoán vị và tổ hợp: vòng `do ... while` vẫn chạy hết, chỉ gọi `print(a)` khi `limit == 0` hoặc `cnt < limit`.
- Gray Code: hàm `graycode()` tự in mã trong vòng lặp nên được thêm tham số `limit`. `benchmark.h` không gọi hàm này nên không phải sửa.

![Output menu 1 khi chỉ in 4 cấu hình đầu tiên](img/week_4_perm_limit.png)

**Điều chỉnh giao diện:**

- Lời nhắc ban đầu dài 51 ký tự, tràn ra ngoài đường viền `----` (44 ký tự), nên được rút gọn còn `So cau hinh muon in (0 = tat ca): ` (34 ký tự).
- Các thông báo lỗi `Loi: ...` được tô đỏ (`\033[31m`), giống dòng `Kiem tra Gray Code: SAI`.

**Mã nguồn:**
- Hàm `readLimit`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L82-L93
- Hàm `graycode` có tham số `limit`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L48-L72
- Hàm `main`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L95-L181

### 2.5. Phân tích độ phức tạp

Tổng thời gian gồm phần sinh, phần kiểm chứng (nếu có) và phần in. Cần phân biệt chi phí sinh một cấu hình với chi phí hiển thị đầy đủ các phần tử của cấu hình đó.

| Thuật toán | Số cấu hình | Chi phí sinh mỗi bước | Tổng thời gian khi in tất cả | Bộ nhớ |
|---|---|---|---|---|
| Hoán vị với phần tử khác nhau | n! | O(n) xấu nhất, O(1) khấu hao | O(n · n!) | O(n) |
| Tổ hợp | C(n, k) | O(k) xấu nhất, O(1) khấu hao khi k ≤ n/2 | O(k · C(n, k)) với k ≥ 1 | O(k) |
| Gray Code | 2ⁿ | O(1) cho công thức sinh mã | O(n · 2ⁿ) với n ≥ 1 | O(2ⁿ) khi kiểm tra bằng seen |

**Hoán vị:** tìm pivot, tìm phần tử thay thế và đảo suffix đều có thể tốn O(n). Với các phần tử khác nhau, suffix dài xuất hiện ít nên chi phí sinh khấu hao là O(1). Tổng phần sinh không in là O(n!), thêm một lần sắp xếp O(n log n). Nếu phần tử trùng nhau, số hoán vị phân biệt là n! / (m₁! · m₂! · ...), trong đó mᵢ là số lần xuất hiện của mỗi giá trị; nhận định khấu hao trên dành cho trường hợp các phần tử khác nhau.

**Tổ hợp:** tìm vị trí cần tăng và đặt lại phần đuôi tốn O(k) xấu nhất. Khi k ≤ n/2, chi phí khấu hao O(1), tổng phần sinh không in O(C(n, k)). Mỗi cấu hình cần O(k) để in. Trường hợp k = 0 chỉ có một tổ hợp rỗng.

**Gray Code:** XOR và dịch bit tốn O(1) trên kiểu số nguyên đang dùng. In bit và duyệt để in tập con đều tốn O(n), nên bổ sung subset không thay đổi bậc độ phức tạp. Mảng seen dùng O(2ⁿ) bộ nhớ phục vụ kiểm chứng; nếu chỉ sinh mã thì bộ nhớ phụ O(1). Trường hợp n = 0 có một tập rỗng.

Giới hạn in chỉ giảm lượng kết quả hiển thị. Chương trình vẫn sinh, đếm đủ và kiểm tra đủ mã Gray, nên n lớn vẫn có thể chạy lâu dù chỉ in vài dòng.

### 2.6. Đánh giá hiệu năng (Benchmark)

#### Phương pháp đo

**Tổ chức mã nguồn:** toàn bộ benchmark nằm trong file header `benchmark.h`, được `#include` vào `comb_gen.cpp` và gọi bằng lựa chọn **4. Benchmark** trên menu. File gồm các hàm:

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/c703bcb/benchmark.h

**Gọi đúng hàm của chương trình:** benchmark gọi luôn `nextPermutation` và `nextCombination` trong `comb_gen.cpp`, nên đo đúng code đã nộp. Gray Code dùng đúng công thức `i ^ (i >> 1)` như menu 3.

**Chỉ đo phần sinh:** không tính thời gian in. Với Gray Code, benchmark cũng không tính `verifyGray()`, vì việc kiểm tra đúng sai đã được thực hiện ở menu 3. Biến `grayXor` giữ lại kết quả các mã Gray, nếu không có biến này thì trình biên dịch sẽ bỏ luôn vòng lặp khi tối ưu `-O2`.

**Kiểm tra số lượng:** mỗi lần chạy đều đếm số cấu hình sinh ra và so với n!, C(n, k), 2ⁿ. Nếu không khớp thì chương trình in `SAI SO LUONG`. Tất cả các dòng đều khớp.

**Lặp lại:** mỗi bộ dữ liệu chạy 1 lần khởi động (không ghi nhận), sau đó chạy 5 lần và lấy **trung vị (median)**.



#### Bộ dữ liệu thử

| Thuật toán | Đầu vào | Lý do chọn |
|---|---|---|
| Hoán vị | n = 8 đến 12, mảng {1, ..., n} | 12! ≈ 4,8 × 10⁸ chạy trong khoảng 1,4 giây, 13! lâu hơn khoảng 13 lần |
| Tổ hợp | n = 16 đến 30 (bước 2), k = n/2 | k = n/2 cho C(n, k) lớn nhất ứng với mỗi n, và n chẵn để k đúng bằng một nửa n |
| Gray Code | n = 16 đến 28 (bước 2) | 2²⁸ ≈ 2,7 × 10⁸ mã, mỗi lần n tăng 2 thì số mã gấp 4 nên dễ đối chiếu |

#### Môi trường và kết quả

**Môi trường đo:** cả ba thuật toán được đo trên máy 1, với cùng phiên bản benchmark.

| Thành phần | Máy 1 |
|---|---|
| CPU | Intel Core i7-11800H (11th Gen), 8 nhân / 16 luồng, 2.30 GHz |
| RAM | 8 GB |
| Trình biên dịch | g++ 12.1.0 (MinGW-W64 x86_64, posix-seh) |
| Cờ biên dịch | `g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen` |
| Bản benchmark | `benchmark.h` bản viết lại ([`1a2a6f6`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1a2a6f6/benchmark.h)) |

Cách đo và bộ dữ liệu như đã trình bày ở trên (1 lần khởi động, 5 lần đo, lấy median). Benchmark không in cấu hình nên phần giới hạn in không ảnh hưởng tới kết quả.

**Điều kiện chạy:** ở lần chạy đầu, số liệu Gray Code dao động từ 0,48 đến 0,62 ns mỗi mã (có thể chịu ảnh hưởng của ứng dụng nền và chế độ nguồn). Nhóm chạy lại 3 lần, cả ba lần đều ra 0,46 đến 0,50 ns. Các bảng dưới đây lấy số liệu của lần đầu tiên trong 3 lần này.

**Bảng 1. Hoán vị (Algorithm L), máy 1**

| n | Số cấu hình (n!) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 8 | 40 320 | 0,1249 | 3,10 |  |  |
| 9 | 362 880 | 1,093 | 3,01 | 8,75 | 9 |
| 10 | 3 628 800 | 10,22 | 2,82 | 9,35 | 10 |
| 11 | 39 916 800 | 113,1 | 2,83 | 11,07 | 11 |
| 12 | 479 001 600 | 1 375 | 2,87 | 12,16 | 12 |

**Bảng 2. Tổ hợp chập k của n (k = n/2), máy 1**

| n | k | Số cấu hình C(n, k) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|---|
| 16 | 8 | 12 870 | 0,0332 | 2,58 |  |  |
| 18 | 9 | 48 620 | 0,125 | 2,57 | 3,77 | 3,78 |
| 20 | 10 | 184 756 | 0,476 | 2,58 | 3,81 | 3,80 |
| 22 | 11 | 705 432 | 1,821 | 2,58 | 3,83 | 3,82 |
| 24 | 12 | 2 704 156 | 7,292 | 2,70 | 4,00 | 3,83 |
| 26 | 13 | 10 400 600 | 28,37 | 2,73 | 3,89 | 3,85 |
| 28 | 14 | 40 116 600 | 104,7 | 2,61 | 3,69 | 3,86 |
| 30 | 15 | 155 117 520 | 414,1 | 2,67 | 3,95 | 3,87 |

**Bảng 3. Gray Code (chỉ sinh mã, không kiểm tra), máy 1**

| n | Số cấu hình (2ⁿ) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 16 | 65 536 | 0,0309 | 0,47 |  |  |
| 18 | 262 144 | 0,1207 | 0,46 | 3,91 | 4 |
| 20 | 1 048 576 | 0,4852 | 0,46 | 4,02 | 4 |
| 22 | 4 194 304 | 1,934 | 0,46 | 3,98 | 4 |
| 24 | 16 777 216 | 7,75 | 0,46 | 4,01 | 4 |
| 26 | 67 108 864 | 32,49 | 0,48 | 4,19 | 4 |
| 28 | 268 435 456 | 128 | 0,48 | 3,94 | 4 |

Toàn bộ kết quả được lưu trong file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv). Ở bản hiện tại, file này và `bench_ns_per_item.csv` đã được chuyển vào thư mục [`results/`](results/).

**Nhận xét:**

1. **Thời gian trên mỗi cấu hình ổn định:** hoán vị khoảng 2,8 đến 3,1 ns mỗi cấu hình, tổ hợp 2,6 đến 2,7 ns, Gray Code 0,46 đến 0,48 ns.
2. **Thời gian tăng đúng theo công thức:** cột tỉ lệ thời gian luôn gần cột tỉ lệ công thức, ví dụ hoán vị từ n = 11 lên 12 chậm đi 12,16 lần (công thức là 12).
3. **Mỗi mã Gray nhanh hơn khoảng 6 lần:** trong benchmark, mỗi mã Gray mất khoảng 0,47 ns, còn mỗi hoán vị hoặc tổ hợp mất 2,6 đến 3,1 ns. Benchmark Gray Code không gọi `verifyGray()` nên con số này không phản ánh trực tiếp tốc độ của menu 3.

### 2.7. Biểu đồ kết quả

Các biểu đồ được vẽ bằng Google Sheets từ file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv) ở mục 2.6:

- **Biểu đồ 1, 2, 3:** tổng thời gian sinh (`median_ms`) theo n, mỗi thuật toán một hình. Trục dọc dùng thang log vì thời gian tăng rất nhanh (hoán vị từ 0,12 ms lên 1 375 ms chỉ sau 4 lần tăng n).
- **Biểu đồ 4:** thời gian sinh một cấu hình (`ns_per_item`) của cả ba thuật toán trên cùng một hình, dữ liệu lấy từ [`bench_ns_per_item.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_ns_per_item.csv) (chỉ xếp lại cột `ns_per_item` cho dễ vẽ).

**Biểu đồ 1, 2, 3. Thời gian sinh theo n của hoán vị (Algorithm L), tổ hợp chập k của n (k = n/2) và Gray Code**

![Bảng bench_results.csv và biểu đồ thời gian sinh theo n của ba thuật toán](img/week_4_chart_time_sheet.png)

**Biểu đồ 4. Thời gian sinh một cấu hình theo n**

![Bảng ns_per_item và biểu đồ thời gian sinh một cấu hình của ba thuật toán theo n](img/week_4_chart_ns_sheet.png)

**Nhận xét:**

1. **Biểu đồ 1, 2, 3 gần như thẳng trên thang log:** thời gian tăng đúng theo số cấu hình. Gray Code tăng theo 2ⁿ, tổ hợp với k = n/2 tăng chậm hơn 2ⁿ một chút. Riêng đường hoán vị hơi cong lên, vì mỗi lần n tăng 1 thì số hoán vị nhân thêm n + 1, hệ số này lớn dần.
2. **Biểu đồ 4 gần như nằm ngang:** thời gian sinh một cấu hình gần như không đổi khi n tăng, đúng với O(1) khấu hao (mục 2.5).
3. **Biểu đồ 2 và 3 giống nhau chỉ là trùng hợp:** Gray Code nhiều cấu hình hơn khoảng 5 đến 7 lần nhưng mỗi cấu hình nhanh hơn khoảng 5,5 lần, nên tổng thời gian xấp xỉ nhau.

### 2.8. Dọn mã nguồn và tăng tốc in kết quả

Nhóm đọc lại `comb_gen.cpp` và sửa thêm vài chỗ nhỏ:

- **Bỏ hàm `legacyNextGray`:** hàm sinh Gray Code cũ, đã không còn được gọi từ khi nhóm chuyển sang công thức `i ^ (i >> 1)`.
- **Tăng tốc phần in:** thêm `ios::sync_with_stdio(false);` ở đầu `main`. Lệnh này tắt đồng bộ giữa `cin`/`cout` với `printf`/`scanf` của C. Chương trình chỉ dùng `cin`/`cout` nên không bị ảnh hưởng gì.
- **Sửa chính tả:** `Greycode` thành `Gray Code` ở lời nhắc menu 3.

**Đo thời gian in:** nhóm cho cả hai bản in hết 10! hoán vị và 2²² mã Gray (khoảng 7,8 triệu dòng) ra file, mỗi bản chạy 2 lần trên máy 2 (g++ 16.2.0, `-O2 -static`).

| Bản | Lần 1 | Lần 2 |
|---|---|---|
| Trước khi sửa (`5d553d1`) | 11,98 s | 11,54 s |
| Sau khi sửa (`997cfa2`) | 5,71 s | 5,90 s |

Thời gian in giảm còn khoảng một nửa, còn output của hai bản giống hệt nhau (kiểm tra bằng lệnh `cmp`). Mỗi bản chỉ chạy 2 lần nên số liệu này dùng để minh họa, chưa đủ để kết luận cho mọi máy. Benchmark ở mục 2.6 không in nên không bị ảnh hưởng.

**Mã nguồn:** commit dọn mã nguồn: https://github.com/QuangquyNguyenvo/DSA_final_project/commit/997cfa2

Phép so sánh output trước/sau ở trên thuộc thời điểm tối ưu nhập xuất, trước khi bổ sung cách in subset. Các ảnh minh chứng cũ có thể chỉ hiển thị chuỗi bit; cách hiển thị hiện tại được minh họa tại mục 2.3.

## 3. Kiểm thử và kiểm chứng

### 3.1. Trace tay

**Hoán vị n = 3, nhập {3, 1, 2}:** Sau khi `sort`, dãy bắt đầu là {1, 2, 3}. Mỗi bước: tìm pivot i (vị trí phải nhất có a[i] < a[i+1]), tìm j (vị trí phải nhất có a[j] > a[i]), đổi chỗ a[i] và a[j], rồi đảo đoạn sau i.

| Bước | Dãy hiện tại | Pivot i | j | Sau khi đổi chỗ | Sau khi đảo đoạn sau i |
|---|---|---|---|---|---|
| 1 | {1, 2, 3} | 1 (2 < 3) | 2 | {1, 3, 2} | {1, 3, 2} |
| 2 | {1, 3, 2} | 0 (1 < 3) | 2 | {2, 3, 1} | {2, 1, 3} |
| 3 | {2, 1, 3} | 1 (1 < 3) | 2 | {2, 3, 1} | {2, 3, 1} |
| 4 | {2, 3, 1} | 0 (2 < 3) | 1 | {3, 2, 1} | {3, 1, 2} |
| 5 | {3, 1, 2} | 1 (1 < 2) | 2 | {3, 2, 1} | {3, 2, 1} |
| 6 | {3, 2, 1} | không có | | | Dừng, trả về `false` |

Output chương trình: `{1, 2, 3}`, `{1, 3, 2}`, `{2, 1, 3}`, `{2, 3, 1}`, `{3, 1, 2}`, `{3, 2, 1}`, `Tong so hoan vi: 6`. Trùng khớp với bảng trace tay theo đúng thứ tự.

![Output chương trình khi chọn menu 1 với n = 3, nhập 3 1 2](img/week_3_perm_n3.png)

**Tổ hợp n = 5, k = 3:** Giá trị tối đa của vị trí i (đánh số từ 0) là n - k + i + 1, tức 3, 4, 5. Mỗi bước: tìm vị trí i phải nhất chưa đạt tối đa, tăng a[i] lên 1, rồi đặt các phần tử sau i tăng dần liên tiếp.

| Bước | Tổ hợp hiện tại | Vị trí i | Tổ hợp kế tiếp |
|---|---|---|---|
| 1 | {1, 2, 3} | 2 | {1, 2, 4} |
| 2 | {1, 2, 4} | 2 | {1, 2, 5} |
| 3 | {1, 2, 5} | 1 (a = 5 đã tối đa) | {1, 3, 4} |
| 4 | {1, 3, 4} | 2 | {1, 3, 5} |
| 5 | {1, 3, 5} | 1 | {1, 4, 5} |
| 6 | {1, 4, 5} | 0 (a = 4, a = 5 đã tối đa) | {2, 3, 4} |
| 7 | {2, 3, 4} | 2 | {2, 3, 5} |
| 8 | {2, 3, 5} | 1 | {2, 4, 5} |
| 9 | {2, 4, 5} | 0 | {3, 4, 5} |
| 10 | {3, 4, 5} | không có | Dừng, trả về `false` |

Output chương trình in đúng 10 tổ hợp theo thứ tự trên và `Tong so to hop: 10`, bằng C(5, 3) = 10.

![Output chương trình khi chọn menu 2 với n = 5, k = 3](img/week_3_comb_5_3.png)

#### Gray Code n = 4

Nhóm trace tay trường hợp n = 4 bằng công thức `G(i) = i ^ (i >> 1)` rồi đối chiếu với output của chương trình.

![Bảng trace tay Gray Code với n = 4](img/week_2_trace_gray_n4.png)

*Hình 3. Bảng trace tay Gray Code với n = 4.*

![Output chương trình khi chọn menu 3 với n = 4](img/week_2_output_gray_n4.png)

*Hình 4. Output của chương trình khi chọn menu 3 với n = 4.*

Kết quả: cả 16 mã trong bảng trace tay trùng khớp với output theo đúng thứ tự. Từ bảng trên có thể thấy thêm hai tính chất:
- Tính phản xạ: 8 mã cuối (i = 8 đến 15) là 8 mã đầu đọc ngược và thêm bit 1 ở đầu.
- Tần suất lật bit: trong 15 bước chuyển, bit 1 bị lật 8 lần, bit 2 lật 4 lần, bit 3 lật 2 lần và bit 4 lật 1 lần. Phần sinh mã trực tiếp bằng XOR có chi phí O(1) mỗi bước.

### 3.2. Các trường hợp kiểm thử

Mã TC được giữ nguyên từ các báo cáo tiến độ. Các mã trùng giữa mục 3.2 và 3.3 thuộc các đợt kiểm thử khác nhau. Kết quả và ảnh kiểm thử cũ được giữ theo thời điểm ghi nhận; phiên bản hiện tại in thêm tập con bên cạnh chuỗi bit Gray Code.

**Sinh hoán vị (menu 1):**

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC10 | Cơ bản (đối chiếu trace tay) | n = 3, {3, 1, 2} | 3! = 6 hoán vị theo thứ tự từ điển | 6 hoán vị khớp bảng trace ở mục 3.1, `Tong so hoan vi: 6` | PASS |
| TC11 | Biên n = 0 | n = 0 | 1 hoán vị rỗng | In `{}`, `Tong so hoan vi: 1` | PASS |
| TC12 | Một phần tử | n = 1, {7} | 1 hoán vị | In `{7}`, `Tong so hoan vi: 1` | PASS |
| TC13 | Có phần tử trùng | n = 3, {1, 1, 2} | 3!/2! = 3 hoán vị, không lặp lại | `{1, 1, 2}`, `{1, 2, 1}`, `{2, 1, 1}`, `Tong so hoan vi: 3` | PASS |
| TC14 | Tất cả phần tử trùng | n = 3, {2, 2, 2} | 1 hoán vị | In `{2, 2, 2}`, `Tong so hoan vi: 1` | PASS |
| TC15 | Kích thước lớn nhất cho phép | n = 10, {1, ..., 10} | 10! = 3 628 800 hoán vị, kết thúc ở dãy giảm dần | Dòng cuối `{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}`, `Tong so hoan vi: 3628800` | PASS |
| TC16 | Dữ liệu không hợp lệ (âm) | n = -1 | Báo lỗi và quay lại menu | `Loi: n phai thoa 0 <= n <= 10` | PASS |
| TC17 | Vượt giới hạn | n = 11 | Báo lỗi và quay lại menu | `Loi: n phai thoa 0 <= n <= 10` | PASS |

Ở TC13 và TC14, chương trình không in hoán vị nào bị lặp lại là nhờ dấu `>=` khi tìm pivot và `<=` khi tìm phần tử thay thế. Pivot chỉ được đổi với một phần tử lớn hơn nó, rồi phần đuôi được đảo để tạo hoán vị kế tiếp theo thứ tự từ điển. Vì mỗi bước đều tăng thứ tự từ điển, chương trình không sinh lại hoán vị đã xuất hiện.

![TC13: hoán vị có phần tử trùng {1, 1, 2}](img/week_3_perm_duplicate.png)

![TC14: hoán vị tất cả phần tử trùng {2, 2, 2}](img/week_3_perm_all_same.png)

**Sinh tổ hợp (menu 2):**

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC18 | Cơ bản (đối chiếu trace tay) | n = 5, k = 3 | C(5, 3) = 10 tổ hợp theo thứ tự từ điển | 10 tổ hợp khớp bảng trace ở mục 3.1, `Tong so to hop: 10` | PASS |
| TC19 | Biên k = 0 | n = 4, k = 0 | 1 tổ hợp rỗng | In `{}`, `Tong so to hop: 1` | PASS |
| TC20 | Biên k = n | n = 4, k = 4 | 1 tổ hợp gồm tất cả phần tử | In `{1, 2, 3, 4}`, `Tong so to hop: 1` | PASS |
| TC21 | Kích thước lớn nhất cho phép | n = 20, k = 10 | C(20, 10) = 184 756 tổ hợp | `Tong so to hop: 184756` | PASS |
| TC22 | k lớn hơn n | n = 3, k = 5 | Báo lỗi và quay lại menu | `Loi: can 0 <= k <= n <= 20` | PASS |
| TC23 | Vượt giới hạn | n = 21, k = 3 | Báo lỗi và quay lại menu | `Loi: can 0 <= k <= n <= 20` | PASS |

![TC22: nhập k lớn hơn n](img/week_3_comb_invalid.png)

**Menu chính:**

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC24 | Nhập chữ thay vì số | `abc` | Thoát chương trình, không treo | Chương trình kết thúc | PASS |

### 3.3. Kiểm chứng số lượng cấu hình với n ≥ 10

Theo yêu cầu đề bài, nhóm kiểm tra tổng số cấu hình của cả ba thuật toán với n ≥ 10 và đối chiếu với công thức lý thuyết.

| Mã | Thuật toán | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC10 | Hoán vị | n = 10, mảng {1, 2, ..., 10} | 10! = 3 628 800 | `Tong so hoan vi: 3628800` | PASS |
| TC11 | Tổ hợp | n = 10, k = 5 | C(10, 5) = 252 | `Tong so to hop: 252` | PASS |
| TC12 | Tổ hợp | n = 20, k = 10 | C(20, 10) = 184 756 | `Tong so to hop: 184756` | PASS |
| TC13 | Tổ hợp, biên k = 0 | n = 10, k = 0 | C(10, 0) = 1 (tập rỗng) | `Tong so to hop: 1` | PASS |
| TC14 | Gray Code | n = 10 | 2^10 = 1 024 | `Tong so ma Gray: 1024`  | PASS |
| TC15 | Hoán vị, toàn phần tử trùng | n = 4, mảng {2, 2, 2, 2} | 1 hoán vị duy nhất | `Tong so hoan vi: 1` | PASS |

> TC15 là edge case "all-duplicate values" mà đề bài nêu. Algorithm L dùng so sánh `>=` khi tìm pivot nên tự bỏ qua các hoán vị trùng nhau và chỉ sinh đúng một cấu hình.

### 3.4. Kiểm thử phần giới hạn số cấu hình được in

Ở mỗi test, nhóm kiểm tra ba điều: chương trình in đúng `limit` cấu hình đầu, có `...` khi còn cấu hình chưa in, và `Tong so ...` vẫn là tổng thật. Mã test giữ nguyên từ báo cáo tiến độ.

| Mã | Menu | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC25 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 2 | In 2 hoán vị đầu, có `...`, tổng 3! = 6 | `{1, 2, 3}`, `{1, 3, 2}`, `...`, `Tong so hoan vi: 6` | PASS |
| TC26 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 0 | In đủ 6 hoán vị như bảng trace tay, không có `...` | 6 hoán vị, `Tong so hoan vi: 6` | PASS |
| TC27 | 1. Hoán vị | n = 2, {1, 2}, `limit` = 2 | `limit` bằng tổng: in đủ 2 hoán vị, không có `...` | `{1, 2}`, `{2, 1}`, `Tong so hoan vi: 2` | PASS |
| TC28 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 100 | `limit` lớn hơn tổng: in đủ 6 hoán vị, không có `...` | 6 hoán vị, `Tong so hoan vi: 6` | PASS |
| TC29 | 1. Hoán vị | n = 10, {1, ..., 10}, `limit` = 3 | In 3 hoán vị đầu, vẫn đếm đủ 10! | 3 hoán vị, `...`, `Tong so hoan vi: 3628800` | PASS |
| TC30 | 2. Tổ hợp | n = 5, k = 2, `limit` = 3 | In 3 tổ hợp đầu, có `...`, tổng C(5, 2) = 10 | `{1, 2}`, `{1, 3}`, `{1, 4}`, `...`, `Tong so to hop: 10` | PASS |
| TC31 | 2. Tổ hợp | n = 5, k = 0, `limit` = 4 | 1 tổ hợp rỗng, không có `...` | `{}`, `Tong so to hop: 1` | PASS |
| TC32 | 2. Tổ hợp | n = 20, k = 10, `limit` = 3 | In 3 tổ hợp đầu, vẫn đếm đủ C(20, 10) | 3 tổ hợp, `...`, `Tong so to hop: 184756` | PASS |
| TC33 | 3. Gray Code | n = 0, `limit` = 5 | 1 mã rỗng, không có `...`, kiểm tra đúng | `{ }`, `Tong so ma Gray: 1`, `Kiem tra Gray Code: DUNG` | PASS |
| TC34 | 3. Gray Code | n = 30, `limit` = 1 | In 1 mã, `verifyGray()` vẫn kiểm tra đủ 2³⁰ mã | 1 mã, `...`, `Tong so ma Gray: 1073741824`, `Kiem tra Gray Code: DUNG` | PASS |
| TC35 | 3. Gray Code | n = 3, `limit` = -1 | Báo lỗi và quay lại menu | `Loi: so cau hinh can in phai >= 0` | PASS |
| TC36 | 3. Gray Code | n = 3, `limit` = `abc` | Báo lỗi, quay lại menu và dùng tiếp được | Bản `f4c36a7`: báo lỗi rồi chương trình thoát. Bản `5d553d1`: báo lỗi, quay lại menu, chạy tiếp menu 3 bình thường | PASS (sau khi sửa) |
---
Ở TC34, Gray Code n = 30 trước đây phải in hơn 1 tỉ dòng, giờ chỉ in 1 dòng mà vẫn sinh và kiểm tra đủ 2³⁰ mã.

![TC34: Gray Code n = 30, chỉ in 1 mã nhưng vẫn đếm và kiểm tra đủ 2³⁰ mã](img/week_4_tc34_gray_n30.png)
---
TC36 lúc đầu không đạt: chương trình báo lỗi đúng nhưng sau đó thoát luôn, không quay lại menu. Nguyên nhân và cách sửa ở mục 6.

![TC36: nhập chữ ở lời nhắc số cấu hình, chương trình báo lỗi rồi quay lại menu](img/week_4_tc36_invalid_limit.png)
---

### 3.5. Kiểm thử bổ sung cho hiển thị subset

Sau khi sửa phần in tập con, chương trình đã được biên dịch và chạy thử với n = 3 và n = 0. Với n = 3, chương trình in đủ 8 cặp chuỗi bit và tập con như mục 2.3. Với n = 0, kết quả là `{ } -> {}`, tổng số mã bằng 1. Cả hai trường hợp đều có `Kiem tra Gray Code: DUNG`.

Các bảng PASS phía trên tổng hợp kiểm thử đã ghi trong README gốc. Đợt sửa hiển thị subset chỉ chạy lại hai trường hợp nêu tại mục này.

## 4. Tích hợp và quản lý mã nguồn

Nhóm sử dụng Git và GitHub để chia nhánh công việc, review qua pull request và theo dõi lịch sử thay đổi. Danh sách commit, pull request và minh chứng từng giai đoạn được lưu trong [README.md](README.md).

| Thành phần | Chức năng |
|---|---|
| `comb_gen.cpp` | Ba thuật toán sinh, kiểm tra Gray Code, nhập liệu, in cấu hình và menu |
| `benchmark.h` | Tính số cấu hình theo công thức, đo thời gian và ghi CSV |
| `results/bench_results.csv` | Dữ liệu benchmark do menu 4 xuất ra |
| `results/bench_ns_per_item.csv` | Dữ liệu sắp xếp lại để vẽ biểu đồ thời gian mỗi cấu hình |
| `img/` | Ảnh minh chứng kế hoạch, trace tay, kiểm thử và biểu đồ |
| `README.md` | Báo cáo tiến độ theo tuần |
| `README_bao_cao_du_an.md` | Báo cáo tổng hợp dự án |

Benchmark gọi trực tiếp `nextPermutation()` và `nextCombination()` của chương trình; Gray Code dùng cùng công thức XOR. Việc kiểm tra mã Gray và hiển thị tập con được thực hiện tại menu 3.

## 5. Phân công công việc

| Thành viên | MSSV | Công việc chính |
|---|---|---|
| Đào Nghiệm Minh | 25110042 | Tham gia nghiên cứu và triển khai thuật toán; xây dựng benchmark ban đầu; thêm `readLimit()` và giới hạn in, điều chỉnh giao diện; đo benchmark trên máy 1, vẽ biểu đồ; bổ sung hiển thị subset và kiểm thử với n = 3, n = 0; tổng hợp báo cáo dự án, cập nhật ảnh benchmark và minh chứng trong cả hai báo cáo. |
| Nguyễn Võ Quang Quý | 25110055 | Tham gia nghiên cứu, triển khai và kiểm chứng thuật toán; review, sửa phép đo Gray Code và viết lại benchmark; trace tay, kiểm thử, xử lý lỗi nhập chữ, dọn mã nguồn, tăng tốc in và viết các phần báo cáo liên quan. |
| Cả nhóm | | Phân tích đề bài, thảo luận kế hoạch, kiểm tra chéo mã nguồn và báo cáo, chuẩn bị vấn đáp và hoàn thiện sản phẩm. |

Phân công chi tiết theo từng giai đoạn được trình bày trong README gốc.

## 6. Khó khăn và hướng giải quyết

- **Tổ chức lại quá trình thực hiện:** sau khi nhận thấy nghiên cứu và kiểm chứng ban đầu chưa đủ kỹ, nhóm bắt đầu lại từ phân tích đề bài, tìm hiểu nguyên lý và trace tay.
- **Xác định bước chuyển đúng thứ tự:** làm rõ pivot, giới hạn từng vị trí và cách đặt lại phần đuôi; đối chiếu kết quả với bảng trace tay.
- **Phép đo Gray Code bản đầu chưa phù hợp:** gọi `verifyGray()` nhưng không sử dụng kết quả có thể dẫn tới phép đo bị tối ưu hoặc gồm chi phí kiểm chứng. Nhóm bỏ kiểm tra khỏi benchmark, XOR dồn vào `grayXor` và đo lại.
- **Kết quả từ hai môi trường khó so sánh:** đo lại ba thuật toán trên máy 1, cùng phiên bản benchmark.
- **In quá nhiều cấu hình:** bổ sung `limit` cho cả ba menu. Chương trình vẫn sinh đủ, nên giới hạn in không loại bỏ chi phí sinh toàn bộ.
- **Nhập chữ tại readLimit() làm chương trình thoát:** dùng `cin.clear()` và `cin.ignore(1000, '\n')` để phục hồi nhập liệu rồi quay lại menu.
- **Chi phí nhập xuất lớn:** thêm `ios::sync_with_stdio(false)` và đo thời gian trước/sau.
- **Chưa thể hiện trực tiếp subset:** in tập con bên cạnh mã bit để người dùng quan sát các phần tử được chọn.
- **Benchmark dao động:** lấy median của năm lần đo sau một lần khởi động và kiểm tra lại khi số liệu biến động.

**Giới hạn hiện tại:** CLI giới hạn kích thước đầu vào; kiểm chứng Gray Code cần bộ nhớ tăng theo 2ⁿ. Phần xử lý nhập chữ ở `readLimit()` và menu chính chưa thay thế cho việc kiểm tra mọi trường nhập. Thời gian đo phụ thuộc môi trường và không bảo đảm giống nhau trên mọi máy.

## 7. Hướng dẫn biên dịch và chạy chương trình

Chương trình được viết bằng C++17, sử dụng trình biên dịch G++. Hai file `comb_gen.cpp` và `benchmark.h` cần nằm cùng một thư mục.

Biên dịch:

```bash
g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen
```

Nếu chương trình bị crash trên Windows do lỗi file `.dll`, thêm cờ `-static` khi biên dịch .

Chạy trên Windows PowerShell:

```powershell
.\comb_gen.exe
```

Chạy trên Linux:

```bash
./comb_gen
```

Menu chương trình:

- **1. Sinh hoán vị (Algorithm L):** nhập n (0 ≤ n ≤ 10) và n phần tử.
- **2. Sinh tổ hợp chập k của n:** nhập n và k (0 ≤ k ≤ n ≤ 20).
- **3. Sinh tập con bằng Gray Code:** nhập n (0 ≤ n ≤ 30).
- **4. Benchmark:** đo thời gian ba thuật toán và ghi kết quả vào `results/bench_results.csv`, nên cần chạy chương trình ở thư mục gốc của repo.
- **0. Thoát.**

Ở menu 1 đến 3, sau khi nhập dữ liệu, chương trình hỏi số cấu hình muốn in (nhập 0 để in tất cả).

Thư mục results/ cần tồn tại. Menu 4 ghi lại bench_results.csv mỗi lần chạy; bench_ns_per_item.csv là dữ liệu sắp xếp lại phục vụ biểu đồ, không được menu này tự động tạo.

## 8. Tổng kết: đối chiếu yêu cầu đề bài

| Yêu cầu đề bài | Tự giải thích | Chi tiết |
|---|---|---|
| Algorithm L | Tìm pivot, đổi với phần tử phải nhất lớn hơn nó rồi đảo suffix để được hoán vị kế tiếp nhỏ nhất. | Mục 2.1, 3.1 |
| Tổ hợp theo thứ tự từ điển | Tăng vị trí phải nhất chưa đạt tối đa và đặt lại phần đuôi tăng liên tiếp. | Mục 2.2, 3.1 |
| Sinh subset bằng Gray Code | Dùng `i ^ (i >> 1)`; in cả chuỗi bit và tập con tương ứng. | Mục 2.3 |
| Số lượng khớp công thức với n ≥ 10 | Đếm cấu hình ở CLI và benchmark; dùng phần tử khác nhau khi đối chiếu n!. | Mục 2.6, 3.3 |
| Hai tập con liên tiếp khác đúng một phần tử | XOR hai mã liên tiếp có đúng một bit 1; kiểm tra bằng popcount. | Mục 2.3 |
| Phân tích chi phí mỗi cấu hình và tổng thời gian | Phân biệt chi phí sinh, in và kiểm chứng; đối chiếu bằng benchmark. | Mục 2.5–2.7 |
| Test nhỏ, lớn và trường hợp biên | Trace tay, kiểm chứng số lượng, đầu vào rỗng, giá trị trùng, k = 0, k = n và nhập sai. | Mục 3 |
| CLI in một số cấu hình đầu | Dùng `limit`; nhập 0 để in tất cả, vẫn sinh và đếm đủ. | Mục 2.4, 7 |

Sản phẩm gồm mã nguồn C++17, CLI, benchmark xuất CSV, bảng kiểm thử, biểu đồ và báo cáo giải thích ba thuật toán.

## 9. Nguồn gốc kiến thức và tài liệu tham khảo

### 9.1. Nguồn gốc kiến thức

Dự án sử dụng kiến thức về tổ hợp, thứ tự từ điển, biểu diễn nhị phân, Boolean Algebra, Karnaugh Map và các phép toán bitwise. Các thuật toán được giải thích qua nguyên lý hoạt động, bảng trace tay và kết quả kiểm thử; phần hiệu năng được đối chiếu với phân tích độ phức tạp.

Báo cáo tổng hợp nội dung, số liệu và minh chứng từ README tiến độ, đồng thời cập nhật phần hiển thị tập con bên cạnh mã Gray. Các tài liệu tham khảo về thuật toán, phép toán bit, đo thời gian và nhập xuất C++ được liệt kê tại mục 9.2.

### 9.2. Tài liệu tham khảo

Các nguồn sau được tổng hợp từ danh sách tài liệu trong README gốc. Danh sách theo từng giai đoạn và video minh chứng được giữ tại [README.md](README.md).

**VNOI Wiki: Phép toán bit**

[https://wiki.vnoi.info/algo/basic/bitwise-operators](https://wiki.vnoi.info/algo/basic/bitwise-operators)

Nội dung liên quan: Các toán tử bitwise, XOR, phép dịch bit và ứng dụng trong lập trình.

**GeeksforGeeks: Generate n-bit Gray Codes**

[https://www.geeksforgeeks.org/dsa/generate-n-bit-gray-codes/](https://www.geeksforgeeks.org/dsa/generate-n-bit-gray-codes/)

Nội dung liên quan: Các phương pháp sinh Gray Code, công thức `G(i) = i ^ (i >> 1)` và ví dụ sinh mã Gray bằng thao tác bitwise.

**CP-Algorithms: Gray Code**

[https://cp-algorithms.com/algebra/gray-code.html](https://cp-algorithms.com/algebra/gray-code.html)

Nội dung liên quan: Binary Reflected Gray Code, công thức chuyển đổi giữa mã nhị phân và mã Gray, cùng các tính chất của dãy Gray Code.

**Viblo: Thao tác xử lý bit và ứng dụng (Bit Manipulation)**

[https://viblo.asia/p/thao-tac-xu-ly-bit-va-ung-dung-bit-manipulation-3kY4gxl9JAe](https://viblo.asia/p/thao-tac-xu-ly-bit-va-ung-dung-bit-manipulation-3kY4gxl9JAe)

Nội dung liên quan: Các thao tác xử lý bit và ứng dụng trong lập trình.

**Stack Overflow: List of ANSI color escape sequences**

[https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences](https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences)

Nội dung liên quan: Danh sách mã ANSI escape dùng để tô màu chữ trên terminal.

**cppreference: std::chrono::steady_clock**

[https://en.cppreference.com/w/cpp/chrono/steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock)

Nội dung liên quan: Đồng hồ đo thời gian không bị ảnh hưởng khi chỉnh giờ hệ thống, dùng để đo thời gian chạy trong benchmark.

**VNOI Wiki: Độ phức tạp thời gian**

[https://wiki.vnoi.info/algo/basic/computational-complexity](https://wiki.vnoi.info/algo/basic/computational-complexity)

Nội dung liên quan: Cách đánh giá độ phức tạp thời gian của thuật toán và ký hiệu Big-O.

**Viblo: Cấu trúc dữ liệu và Giải thuật Bài 3: Độ phức tạp thời gian (Time Complexity) và Ký pháp Big-O**

[https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-3-do-phuc-tap-thoi-gian-time-complexity-va-ky-phap-big-o-1QLxnmjO4Aw](https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-3-do-phuc-tap-thoi-gian-time-complexity-va-ky-phap-big-o-1QLxnmjO4Aw)

Nội dung liên quan: Đánh giá thuật toán theo tốc độ tăng của số phép toán thay vì thời gian đo bằng giây, các cấp độ phức tạp thường gặp.

**Viblo: Cấu trúc dữ liệu và Giải thuật Bài 8: Giới thiệu về Amortized Analysis (Phân tích khấu hao)**

[https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-8-gioi-thieu-ve-amortized-analysis-phan-tich-khau-hao-pPLkNbleJRZ](https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-8-gioi-thieu-ve-amortized-analysis-phan-tich-khau-hao-pPLkNbleJRZ)

Nội dung liên quan: Phân tích khấu hao, tính chi phí trung bình của một thao tác trong một chuỗi thao tác liên tiếp.

**GeeksforGeeks: Measure execution time of a function in C++**

[https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/](https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/)

Nội dung liên quan: Đo thời gian chạy của một hàm bằng thư viện `<chrono>`, lấy thời điểm trước và sau khi chạy rồi tính hiệu.

**USACO Guide: Time Complexity**

[https://usaco.guide/bronze/time-comp](https://usaco.guide/bronze/time-comp)

Nội dung liên quan: Ký hiệu Big-O, độ phức tạp của các vòng lặp, độ phức tạp O(2ⁿ) khi duyệt mọi tập con và O(n!) khi duyệt mọi hoán vị.

**GeeksforGeeks: How to Handle Wrong Data Type Input in C++?**

[https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/](https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/)

Nội dung liên quan: Xử lý khi người dùng nhập sai kiểu dữ liệu, dùng `cin.clear()` để xóa trạng thái lỗi của `cin` và `cin.ignore()` để bỏ phần nhập sai còn lại.

**GeeksforGeeks: Fast I/O for Competitive Programming**

[https://www.geeksforgeeks.org/dsa/fast-io-for-competitive-programming/](https://www.geeksforgeeks.org/dsa/fast-io-for-competitive-programming/)

Nội dung liên quan: Tăng tốc nhập xuất bằng `ios_base::sync_with_stdio(false)`, tắt đồng bộ giữa luồng nhập xuất của C++ và C.

**Viblo: Các kĩ năng thi cử 10.1: Kĩ thuật tối ưu tốc độ chương trình C++**

[https://viblo.asia/p/cac-ki-nang-thi-cu-101-ki-thuat-toi-uu-toc-do-chuong-trinh-c-Yym40njjL91](https://viblo.asia/p/cac-ki-nang-thi-cu-101-ki-thuat-toi-uu-toc-do-chuong-trinh-c-Yym40njjL91)

Nội dung liên quan: Giải thích vì sao tắt đồng bộ giữa `cin`, `cout` với luồng chuẩn của C giúp chương trình nhập xuất nhanh hơn.
