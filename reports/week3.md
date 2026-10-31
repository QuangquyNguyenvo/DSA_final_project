# BÁO CÁO TIẾN ĐỘ (Tuần 3): Hoàn thiện CLI, phân tích độ phức tạp và đánh giá hiệu năng

**Môn học:** Cấu trúc dữ liệu và Giải thuật.

**Mã lớp học phần:** DASA230179_Dot1, HK1 2026-2027.

**Giảng viên hướng dẫn:** Huỳnh Xuân Phụng.

**GitHub Repository:** https://github.com/QuangquyNguyenvo/DSA_final_project

## 1. Tổng quan

Sau hai tuần đầu, `comb_gen.cpp` đã có đủ ba thuật toán. Sang tuần 3, nhóm chuyển trọng tâm từ cài đặt sang hoàn thiện chương trình và đánh giá thuật toán.

Mục tiêu của tuần này:
- Hoàn thiện CLI: menu rõ ràng, tô màu kết quả, kiểm tra dữ liệu đầu vào cho cả ba thuật toán.
- Phân tích trường hợp xấu nhất, chi phí khấu hao (amortized) mỗi bước và tổng thời gian sinh của từng thuật toán.
- Xây dựng benchmark, đo thời gian chạy thực tế và đối chiếu với kết quả phân tích lý thuyết.
- Bổ sung kiểm thử cho sinh hoán vị và sinh tổ hợp (tuần 2 mới kiểm thử Gray Code), gồm trace tay, trường hợp biên và dữ liệu lớn.

**Minh chứng:**
![Kế hoạch tuần 3 được viết tay trên Scrble](../img/week_3_planning.png)

## 2. Công việc thực hiện

### 2.1. Thiết kế CLI

Chương trình `comb_gen.cpp` chạy trên terminal với một menu lặp lại liên tục: người dùng chọn chức năng, nhập dữ liệu, xem kết quả, rồi quay lại menu cho tới khi chọn **0. Thoat**.

```
===========COMBINATION GENERATOR===========
     1. Sinh hoan vi (Algorithm L)
     2. Sinh to hop chap k cua n
     3. Sinh tap con bang Gray Code
     4. Benchmark
     0. Thoat
============================================
  -> Lua chon:
```

![Menu chính của chương trình](../img/week_3_menu.png)

**Tô màu bằng mã ANSI escape [1]:**

| Mã | Màu | Dùng cho |
|---|---|---|
| `\033[33m` | Vàng | Tiêu đề, menu và các đường viền `====` |
| `\033[36m` | Xanh lơ | Dòng nhắc lựa chọn, tổng số cấu hình, kết quả kiểm tra Gray Code DUNG |
| `\033[31m` | Đỏ | Kết quả kiểm tra Gray Code SAI |
| `\033[0m` | | Trả về màu mặc định sau mỗi dòng |

Các dòng `----` ngăn cách phần nhập dữ liệu với phần kết quả cho dễ đọc. Màu chỉ hiển thị đúng trên terminal hỗ trợ ANSI (như Windows Terminal, terminal của VS Code). Terminal cũ không hỗ trợ sẽ in nguyên các mã như `[33m`.

**Nhập dữ liệu và kiểm tra đầu vào:**

| Lựa chọn | Dữ liệu nhập | Điều kiện hợp lệ | Lý do giới hạn |
|---|---|---|---|
| 1. Hoán vị | n, rồi lần lượt n phần tử | 0 ≤ n ≤ 10 | n âm có thể gây crash, n lớn in quá nhiều dòng (10! ≈ 3,6 triệu) |
| 2. Tổ hợp | n, rồi k (chọn k phần tử từ {1, ..., n}) | 0 ≤ k ≤ n ≤ 20 | k > n không có tổ hợp, n lớn in quá nhiều dòng |
| 3. Gray Code | n | 0 ≤ n ≤ 30 | n âm làm `1 << n` không hợp lệ, n > 30 làm `1 << n` tràn `int` |

- Nhập sai điều kiện thì chương trình báo lỗi (ví dụ `Loi: n phai thoa 0 <= n <= 30`) và quay lại menu.
- Nhập chữ thay vì số ở menu thì chương trình thoát vòng lặp và kết thúc.
- Với hoán vị, các phần tử nhập vào được sắp xếp trước, để bắt đầu sinh từ hoán vị nhỏ nhất theo thứ tự từ điển.

**Hiển thị kết quả:**

- Mỗi cấu hình in trên một dòng: hoán vị và tổ hợp dạng `{1, 2, 3}`, Gray Code dạng dãy bit `{ 0 1 1 }`.
- Cuối mỗi lần chạy in tổng số cấu hình (`Tong so hoan vi`, `Tong so to hop`, `Tong so ma Gray`) để đối chiếu với n!, C(n, k), 2ⁿ.
- Gray Code in thêm kết quả kiểm tra của `verifyGray()`: `Kiem tra Gray Code: DUNG` (xanh) hoặc `SAI` (đỏ).
- Lựa chọn **4. Benchmark** chạy phần đo hiệu năng, trình bày ở mục 2.3.

**Mã nguồn hàm `main`:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L90-L165

---

### 2.2. Phân tích độ phức tạp

#### Nguyên tắc chung

Cả 3 thuật toán đều dùng chung một cách tính [3], [4], [7]:

> **Tổng thời gian = (số lần vòng lặp chạy) × (chi phí hàm sinh kế tiếp + chi phí `print`)**

Số lần lặp nằm ở vòng `do while` hoặc `for` trong `main` hay `graycode`. Chi phí mỗi bước nằm trong các vòng `while`, `for` và lệnh `reverse` bên trong hàm sinh. Số dòng dưới đây tính theo mã nguồn ở commit [`faf925f`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp).

---

#### 2.2.1. Sinh hoán vị: `nextPermutation`

**Số lần lặp:** vòng `do while` ở **dòng 117 đến 120** chạy **n!** lần (nếu các phần tử khác nhau đôi một).

**Chi phí mỗi lần gọi:**

| Dòng | Đoạn code | Trường hợp xấu nhất |
|---|---|---|
| 10 | `while(i>=0 && a[i]>=a[i+1]) i--;` (tìm pivot) | O(n) |
| 14 | `while(a[j]<=a[i]) j--;` (tìm phần tử thay thế) | O(n) |
| 17 | `reverse(a.begin()+i+1, a.end());` | O(n) |

- Trường hợp xấu nhất mỗi bước là **O(n)**, xảy ra khi pivot nằm ở đầu dãy (ví dụ đi từ {1, 4, 3, 2} sang {2, 1, 3, 4}).
- Tính trung bình (amortized) thì chỉ **O(1)** [5], vì phần lớn các lần gọi có pivot nằm ngay gần cuối dãy. Ở bảng trace n = 3 (mục 3.1), trong 5 lần sinh có 3 lần pivot nằm ở vị trí áp chót, chỉ 2 lần phải lùi về đầu dãy. Pivot càng nằm xa cuối dãy thì trường hợp đó càng hiếm, nên số bước trung bình bị chặn bởi một hằng số nhỏ. Số liệu ở Bảng 1 (mục 2.3) phù hợp với nhận định này: thời gian sinh một hoán vị gần như không đổi khi n tăng từ 8 đến 12.
- `print(a)` ở dòng 118 tốn **O(n)**.
- `sort` ở dòng 114 tốn O(n log n) nhưng chỉ chạy một lần, nên không đáng kể.

>**Kết luận:** Thời gian **O(n · n!)**, bị chi phối bởi việc in. Nếu không in thì là **O(n!)**. Bộ nhớ **O(n)**.

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L8-L19

---

#### 2.2.2. Sinh tổ hợp chập k của n: `nextCombination`

**Số lần lặp:** vòng `do while` ở **dòng 139 đến 142** chạy **C(n, k)** lần.

**Chi phí mỗi lần gọi:**

| Dòng | Đoạn code | Trường hợp xấu nhất |
|---|---|---|
| 23 | `while(i>=0 && a[i]==n-k+i+1) i--;` (bỏ qua các vị trí đã đạt tối đa) | O(k) |
| 26 | `for(int j=i+1;j<k;j++) a[j]=a[j-1]+1;` (đặt lại phần đuôi) | O(k) |

- Xấu nhất **O(k)** mỗi bước, ví dụ đi từ {1, 4, 5} sang {2, 3, 4} với n = 5, k = 3.
- Trung bình gần như hằng số khi k ≤ n/2, vì đa số lần chỉ có phần tử cuối tăng lên. Số liệu benchmark ở mục 2.3 (k = n/2) cũng cho thấy thời gian sinh mỗi cấu hình gần như không đổi khi n tăng.
- `print(a)` ở dòng 140 tốn **O(k)**.

>**Kết luận:** Thời gian **O(k · C(n, k))**. Nếu không in thì là **O(C(n, k))** khi k ≤ n/2. Bộ nhớ **O(k)**.

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L20-L28

---

#### 2.2.3. Sinh tập con bằng Gray Code: `graycode`

**Số lần lặp:** vòng `for` ở **dòng 68** chạy **2ⁿ** lần.

**Chi phí mỗi vòng:**

| Dòng | Đoạn code | Chi phí |
|---|---|---|
| 69 | `int gray= i^(i>>1);` | O(1) |
| 71 | `for(int j=n-1; j>=0;j--)` in từng bit | **O(n)**, chi phí chính |
| 74, hàm `verifyGray` (dòng 43 đến 59) | tra mảng `seen` và `__builtin_popcount` | O(1) |

**Bộ nhớ:** `vector<bool> seen(total, false)` ở **dòng 63** tốn **O(2ⁿ)**. Đây là chỗ duy nhất trong 3 thuật toán có bộ nhớ tăng theo hàm mũ, và nó chỉ phục vụ việc kiểm tra, không phục vụ việc sinh mã.

>**Kết luận:** Thời gian **O(n · 2ⁿ)** do in, phần sinh mã chỉ **O(1)** mỗi bước, không cần khấu hao. Bộ nhớ **O(2ⁿ)** (bỏ phần kiểm tra thì chỉ còn O(1)).

**Ghi chú:** Hàm `legacyNextGray` (dòng 29) không được gọi trong `main`. Nếu dùng nó, vòng `while` ở dòng 33 tốn O(n) mỗi bước trong trường hợp xấu nhất.

**Mã nguồn:**
- Hàm `graycode`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L61-L80
- Hàm `verifyGray`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L43-L59

---

**Tóm tắt:**

| Thuật toán | Số lần lặp (dòng) | Chi phí mỗi bước (dòng) | Tổng thời gian | Bộ nhớ |
|---|---|---|---|---|
| Hoán vị | n! (117) | O(n) xấu nhất, O(1) khấu hao (10, 14, 17) | O(n · n!) | O(n) |
| Tổ hợp chập k | C(n, k) (139) | O(k) xấu nhất, O(1) khấu hao khi k ≤ n/2 (23, 26) | O(k · C(n, k)) | O(k) |
| Gray Code | 2ⁿ (68) | O(1) sinh mã (69), O(n) do in (71) | O(n · 2ⁿ) | O(2ⁿ) (63) |

>**Nhận xét:** Số lần lặp của cả 3 thuật toán bằng đúng số cấu hình cần sinh (n!, C(n, k), 2ⁿ). Muốn in hết các cấu hình thì ít nhất phải lặp chừng đó lần, nên số lần lặp không thể giảm thêm. Hệ số n hoặc k nhân thêm là do mỗi cấu hình có n hoặc k phần tử cần in ra.

---

### 2.3. Đánh giá hiệu năng (Benchmark)

#### 2.3.1. Mục tiêu

Dùng số liệu đo thật để kiểm tra hai kết luận ở mục 2.2:
- Tổng thời gian tăng đúng theo n!, C(n, k), 2ⁿ.
- Thời gian sinh một cấu hình gần như không đổi khi n tăng (O(1) khấu hao).

#### 2.3.2. Môi trường đo

Bảng 1 và Bảng 2 đo trên máy của Minh bằng bản benchmark đầu (commit `edbfebe`). Bảng 3 được đo lại trên máy của Quý bằng bản viết lại (commit `1a2a6f6`), sau khi sửa lỗi phép đo Gray Code (xem mục 2.3.3 và mục 6). Hai máy dùng cùng CPU, chỉ khác dung lượng RAM, phiên bản trình biên dịch và cờ `-static`.

| Thành phần | Máy 1 (Bảng 1, 2) | Máy 2 (Bảng 3) |
|---|---|---|
| CPU | Intel Core i7-11800H (11th Gen), 8 nhân / 16 luồng, 2.30 GHz | Intel Core i7-11800H (11th Gen), 8 nhân / 16 luồng, 2.30 GHz |
| RAM | 8 GB | 16 GB |
| Trình biên dịch | g++ 12.1.0 (MinGW-W64 x86_64, posix-seh) | g++ 16.2.0 (MinGW-W64 x86_64, ucrt-posix-seh) |
| Cờ biên dịch | `g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen` | `g++ -std=c++17 -O2 -static comb_gen.cpp -o comb_gen` |
| Đồng hồ đo | `std::chrono::steady_clock` [2], [6] | `std::chrono::steady_clock` [2], [6] |

#### 2.3.3. Phương pháp đo

**Tổ chức mã nguồn:** toàn bộ benchmark nằm trong file header `benchmark.h`, được `#include` vào `comb_gen.cpp` và gọi bằng lựa chọn **4. Benchmark** trên menu. File gồm các hàm:

| Hàm | Dòng | Chức năng |
|---|---|---|
| `fact`, `binom` | 13 đến 23 | Tính số cấu hình theo công thức n! và C(n, k) |
| `generate` | 26 đến 45 | Sinh toàn bộ cấu hình nhưng không in, trả về số cấu hình đếm được |
| `measure` | 48 đến 58 | Chạy 1 lần khởi động và 5 lần đo, trả về median |
| `runAlgo` | 61 đến 89 | Đo một thuật toán với n chạy trong một khoảng, in và ghi từng dòng kết quả |
| `runBenchmark` | 91 đến 101 | Gọi `runAlgo` cho 3 thuật toán và ghi file `bench_results.csv` |

**Mã nguồn:** https://github.com/QuangquyNguyenvo/DSA_final_project/blob/c703bcb/benchmark.h

**Gọi đúng hàm của chương trình:** benchmark gọi luôn `nextPermutation` và `nextCombination` trong `comb_gen.cpp`, nên đo đúng code đã nộp. Gray Code dùng đúng công thức `i ^ (i >> 1)` như menu 3.

**Chỉ đo phần sinh:** không tính thời gian in. Với Gray Code, benchmark cũng không tính `verifyGray()`, vì việc kiểm tra đúng sai đã được thực hiện ở menu 3. Biến `grayXor` giữ lại kết quả các mã Gray, nếu không có biến này thì trình biên dịch sẽ bỏ luôn vòng lặp khi tối ưu `-O2`.

**Kiểm tra số lượng:** mỗi lần chạy đều đếm số cấu hình sinh ra và so với n!, C(n, k), 2ⁿ. Nếu không khớp thì chương trình in `SAI SO LUONG`. Tất cả các dòng đều khớp.

**Lặp lại:** mỗi bộ dữ liệu chạy 1 lần khởi động (không ghi nhận), sau đó chạy 5 lần và lấy **trung vị (median)**.

**Hai phiên bản benchmark:** bản đầu do Minh viết ([`edbfebe`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/edbfebe/benchmark.h)), sau đó Quý review và viết lại ([`1a2a6f6`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1a2a6f6/benchmark.h)). Các thay đổi:

| Nội dung | Bản đầu (`edbfebe`) | Bản viết lại (`1a2a6f6`) |
|---|---|---|
| Tổ chức mã | Mỗi thuật toán một hàm riêng (`genPerm`, `genComb`, `genGray`), đo qua template `medianMs` và lambda | Gộp vào một hàm `generate`, đo qua `measure` và `runAlgo`, mã ngắn và dễ đọc hơn |
| Đo hoán vị | Sinh từ {1, ..., n}, đếm số cấu hình, gọi `nextPermutation` | Giữ nguyên cách đo |
| Đo tổ hợp | Sinh từ {1, ..., k}, đếm số cấu hình, gọi `nextCombination` | Giữ nguyên cách đo |
| Đo Gray Code | Gọi `verifyGray()` cho mỗi mã nhưng không dùng kết quả trả về | Bỏ `verifyGray()`, XOR các mã Gray vào biến `grayXor` để trình biên dịch không bỏ vòng lặp |
| Đếm số cấu hình | Biến toàn cục `bCnt` | `generate` trả về số cấu hình đếm được |
| Bảng kết quả dùng trong báo cáo | Bảng 1, Bảng 2 | Bảng 3 |

Vì cách đo hoán vị và tổ hợp không đổi giữa hai phiên bản, Bảng 1 và Bảng 2 đo bằng bản đầu vẫn dùng được. Chỉ phép đo Gray Code phải đo lại.

**Các cột trong bảng kết quả** (cũng được ghi vào `bench_results.csv` để vẽ biểu đồ ở tuần 4):
  - `total_ms`: tổng thời gian sinh toàn bộ cấu hình (median).
  - `ns/cấu hình` = total_ms × 1 000 000 / số cấu hình, tức thời gian sinh một cấu hình.
  - `Tỉ lệ thời gian` và `Tỉ lệ công thức`: thời gian và số cấu hình của dòng này chia cho dòng trước. Hai tỉ lệ gần bằng nhau nghĩa là thời gian tăng đúng theo công thức.

#### 2.3.4. Bộ dữ liệu thử

| Thuật toán | Đầu vào | Lý do chọn |
|---|---|---|
| Hoán vị | n = 8 đến 12, mảng {1, ..., n} | 12! ≈ 4,8 × 10⁸ chạy trong khoảng 1,4 giây, 13! lâu hơn khoảng 13 lần |
| Tổ hợp | n = 16 đến 30 (bước 2), k = n/2 | k = n/2 cho C(n, k) lớn nhất ứng với mỗi n, và n chẵn để k đúng bằng một nửa n |
| Gray Code | n = 16 đến 28 (bước 2) | 2²⁸ ≈ 2,7 × 10⁸ mã, mỗi lần n tăng 2 thì số mã gấp 4 nên dễ đối chiếu |

#### 2.3.5. Kết quả

**Bảng 1. Hoán vị (Algorithm L), máy 1**

| n | Số cấu hình (n!) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 8 | 40 320 | 0,122 | 3,03 | | |
| 9 | 362 880 | 1,087 | 2,99 | 8,91 | 9 |
| 10 | 3 628 800 | 11,13 | 3,07 | 10,24 | 10 |
| 11 | 39 916 800 | 117,5 | 2,94 | 10,56 | 11 |
| 12 | 479 001 600 | 1 393 | 2,91 | 11,86 | 12 |

**Bảng 2. Tổ hợp chập k của n (k = n/2), máy 1**

| n | k | Số cấu hình C(n, k) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|---|
| 16 | 8 | 12 870 | 0,034 | 2,63 | | |
| 18 | 9 | 48 620 | 0,130 | 2,68 | 3,85 | 3,78 |
| 20 | 10 | 184 756 | 0,495 | 2,68 | 3,80 | 3,80 |
| 22 | 11 | 705 432 | 1,893 | 2,68 | 3,83 | 3,82 |
| 24 | 12 | 2 704 156 | 7,222 | 2,67 | 3,81 | 3,83 |
| 26 | 13 | 10 400 600 | 27,37 | 2,63 | 3,79 | 3,85 |
| 28 | 14 | 40 116 600 | 106,5 | 2,65 | 3,89 | 3,86 |
| 30 | 15 | 155 117 520 | 416,1 | 2,68 | 3,91 | 3,87 |

**Bảng 3. Gray Code (chỉ sinh mã, không kiểm tra), máy 2**

| n | Số cấu hình (2ⁿ) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 16 | 65 536 | 0,029 | 0,45 | | |
| 18 | 262 144 | 0,118 | 0,45 | 4,01 | 4 |
| 20 | 1 048 576 | 0,471 | 0,45 | 4,00 | 4 |
| 22 | 4 194 304 | 1,887 | 0,45 | 4,01 | 4 |
| 24 | 16 777 216 | 7,865 | 0,47 | 4,17 | 4 |
| 26 | 67 108 864 | 31,48 | 0,47 | 4,00 | 4 |
| 28 | 268 435 456 | 125,6 | 0,47 | 3,99 | 4 |

Output khi chọn menu 4 trên máy 2 (Bảng 3 lấy từ lần chạy này) và file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/dbce015/bench_results.csv) được ghi ra:

![Output chương trình khi chọn menu 4 Benchmark](../img/week_3_benchmark.png)

![File bench_results.csv sau khi chạy benchmark](../img/week_3_benchmark_csv.png)

#### 2.3.6. Phân tích và nhận xét

**Kỳ vọng theo lý thuyết** (dùng để đối chiếu với số liệu ở 2.3.5):

| Thuật toán | Tổng thời gian (không in) | Tỉ lệ kỳ vọng khi tăng n | ns/cấu hình |
|---|---|---|---|
| Hoán vị | Θ(n!) | t(n+1) / t(n) ≈ n + 1 | Gần như không đổi |
| Tổ hợp | Θ(C(n, k)) khi k ≤ n/2 | t(n+2) / t(n) ≈ C(n+2, k+1) / C(n, k) | Gần như không đổi |
| Gray Code | Θ(2ⁿ) | t(n+2) / t(n) ≈ 4 | Không đổi, mỗi bước O(1) |

Có in ra thì mỗi bước tốn thêm O(n) hoặc O(k), nên tổng thời gian trở thành:

**O(n · n!)** với hoán vị, **O(k · C(n, k))** với tổ hợp và **O(n · 2ⁿ)** với Gray Code.

**Nhận xét theo số liệu đo:**

1. **Thời gian tăng đúng theo công thức:** cột tỉ lệ thời gian gần bằng cột tỉ lệ công thức. Ví dụ hoán vị từ n = 11 lên 12 thì thời gian tăng 11,86 lần, công thức là 12 lần. Với Gray Code, mỗi lần n tăng 2 thì thời gian tăng khoảng 4,0 đến 4,2 lần, công thức là 4 lần.
2. **Mỗi bước tốn thời gian gần như không đổi:** cột ns/cấu hình gần như không đổi khi n tăng: hoán vị khoảng 3 ns, tổ hợp khoảng 2,7 ns, Gray Code khoảng 0,45 ns. Với hoán vị và tổ hợp, dù có bước tốn O(n) hoặc O(k), tính trung bình thì mỗi bước vẫn chỉ tốn một khoảng thời gian cố định (O(1) khấu hao). Với Gray Code, mọi bước đều là O(1). Kết quả này phù hợp với phân tích ở mục 2.2.
3. **Gray Code nhanh nhất:** mỗi bước chỉ có một phép XOR và một phép dịch bit, còn hoán vị và tổ hợp phải chạy vòng `while` để tìm vị trí cần đổi (dù trung bình vòng này chỉ chạy vài lần). Vì Bảng 1, 2 và Bảng 3 đo trên hai máy với hai phiên bản trình biên dịch khác nhau, nhóm so sánh trong cùng lần chạy trên máy 2 (ảnh output menu 4 ở trên): hoán vị và tổ hợp khoảng 2,4 đến 3,1 ns mỗi cấu hình, còn Gray Code chỉ khoảng 0,45 ns, nhanh hơn khoảng 6 lần.

## 3. Kiểm thử và kiểm chứng

Tuần 2 đã kiểm thử Gray Code (9 test case, trace tay n = 4). Tuần 3 bổ sung kiểm thử cho sinh hoán vị và sinh tổ hợp. Mọi kết quả thực tế dưới đây lấy từ output của chương trình ở commit `faf925f`.

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

![Output chương trình khi chọn menu 1 với n = 3, nhập 3 1 2](../img/week_3_perm_n3.png)

**Tổ hợp n = 5, k = 3:** Giá trị tối đa của vị trí i (đánh số từ 0) là n - k + i + 1, tức 3, 4, 5. Mỗi bước: tìm vị trí i phải nhất chưa đạt tối đa, tăng a[i] lên 1, rồi đặt các phần tử sau i tăng dần liên tiếp.

| Bước | Tổ hợp hiện tại | Vị trí i | Tổ hợp kế tiếp |
|---|---|---|---|
| 1 | {1, 2, 3} | 2 | {1, 2, 4} |
| 2 | {1, 2, 4} | 2 | {1, 2, 5} |
| 3 | {1, 2, 5} | 1 (a[2] = 5 đã tối đa) | {1, 3, 4} |
| 4 | {1, 3, 4} | 2 | {1, 3, 5} |
| 5 | {1, 3, 5} | 1 | {1, 4, 5} |
| 6 | {1, 4, 5} | 0 (a[1] = 4, a[2] = 5 đã tối đa) | {2, 3, 4} |
| 7 | {2, 3, 4} | 2 | {2, 3, 5} |
| 8 | {2, 3, 5} | 1 | {2, 4, 5} |
| 9 | {2, 4, 5} | 0 | {3, 4, 5} |
| 10 | {3, 4, 5} | không có | Dừng, trả về `false` |

Output chương trình in đúng 10 tổ hợp theo thứ tự trên và `Tong so to hop: 10`, bằng C(5, 3) = 10.

![Output chương trình khi chọn menu 2 với n = 5, k = 3](../img/week_3_comb_5_3.png)

### 3.2. Các trường hợp kiểm thử

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

Ở TC13 và TC14, chương trình không in hoán vị nào bị lặp lại là nhờ dấu `>=` ở dòng 10 và `<=` ở dòng 14. Pivot chỉ được đổi với một phần tử lớn hơn nó, rồi phần đuôi được đảo để tạo hoán vị kế tiếp theo thứ tự từ điển. Vì mỗi bước đều tăng thứ tự từ điển, chương trình không sinh lại hoán vị đã xuất hiện.

![TC13: hoán vị có phần tử trùng {1, 1, 2}](../img/week_3_perm_duplicate.png)

![TC14: hoán vị tất cả phần tử trùng {2, 2, 2}](../img/week_3_perm_all_same.png)

**Sinh tổ hợp (menu 2):**

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC18 | Cơ bản (đối chiếu trace tay) | n = 5, k = 3 | C(5, 3) = 10 tổ hợp theo thứ tự từ điển | 10 tổ hợp khớp bảng trace ở mục 3.1, `Tong so to hop: 10` | PASS |
| TC19 | Biên k = 0 | n = 4, k = 0 | 1 tổ hợp rỗng | In `{}`, `Tong so to hop: 1` | PASS |
| TC20 | Biên k = n | n = 4, k = 4 | 1 tổ hợp gồm tất cả phần tử | In `{1, 2, 3, 4}`, `Tong so to hop: 1` | PASS |
| TC21 | Kích thước lớn nhất cho phép | n = 20, k = 10 | C(20, 10) = 184 756 tổ hợp | `Tong so to hop: 184756` | PASS |
| TC22 | k lớn hơn n | n = 3, k = 5 | Báo lỗi và quay lại menu | `Loi: can 0 <= k <= n <= 20` | PASS |
| TC23 | Vượt giới hạn | n = 21, k = 3 | Báo lỗi và quay lại menu | `Loi: can 0 <= k <= n <= 20` | PASS |

![TC22: nhập k lớn hơn n](../img/week_3_comb_invalid.png)

**Menu chính:**

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC24 | Nhập chữ thay vì số | `abc` | Thoát chương trình, không treo | Chương trình kết thúc | PASS |

### 3.3. Kiểm chứng số lượng cấu hình với dữ liệu lớn

Benchmark đếm đúng số cấu hình ở mọi bộ dữ liệu, lớn nhất là 12!, C(30, 15) và 2²⁸. Cùng với TC15, TC21 và các test Gray Code tuần 2, cả ba thuật toán đã được kiểm tra số lượng với n từ 10 trở lên, đúng yêu cầu 4 của đề.

## 4. Tích hợp và quản lý mã nguồn

Công việc tuần 3 được thực hiện trên nhánh `week3` và tích hợp vào `main` qua PR #9, #10. Các chỉnh sửa sau khi review (viết lại benchmark, sửa lời nhắc menu) được thực hiện trên nhánh `review/week3` và tích hợp vào `main` qua PR #11.

**Mã nguồn:**
- Hàm `main` với menu tô màu ANSI và kiểm tra đầu vào: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L90-L165
- Sinh hoán vị (`nextPermutation`): https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L8-L19
- Sinh tổ hợp (`nextCombination`): https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L20-L28
- Sinh Gray Code (`graycode`) và hàm kiểm tra (`verifyGray`): https://github.com/QuangquyNguyenvo/DSA_final_project/blob/faf925f/comb_gen.cpp#L43-L80
- File benchmark: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/c703bcb/benchmark.h
- Kết quả benchmark: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/dbce015/bench_results.csv

**Pull Request:**
- PR #9 (`week3`, Đào Nghiệm Minh): hoàn thiện giao diện CLI, thêm báo cáo tuần 3 và phần phân tích độ phức tạp: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/9
- PR #10 (`week3`, Đào Nghiệm Minh): bổ sung phần tổng quan, thiết kế CLI và benchmark: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/10
- PR #11 (`review/week3`, Nguyễn Võ Quang Quý): viết lại benchmark, sửa phép đo Gray Code, bổ sung kiểm thử và hoàn thiện báo cáo tuần 3: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/11

**Commit:**
- [`ae634c2`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/ae634c2): tô màu menu và kết quả bằng mã ANSI, thêm khung viền và đổi lời nhắc nhập dữ liệu cho rõ ràng (Minh).
- [`3e8d482`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/3e8d482): thêm báo cáo tuần 3 và phân tích độ phức tạp (Minh).
- [`6ddda19`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/6ddda19): merge PR #9, tích hợp tuần 3 vào `main`.
- [`d8f1ace`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/d8f1ace): bổ sung phần tổng quan, thiết kế CLI và kế hoạch tuần 4 (Minh).
- [`edbfebe`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/edbfebe): thêm benchmark so sánh thời gian chạy với công thức vào menu CLI (Minh).
- [`964e0e1`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/964e0e1): merge PR #10.
- [`1a2a6f6`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/1a2a6f6): viết lại benchmark gọn hơn, sửa phép đo Gray Code bị trình biên dịch tối ưu mất (Quý).
- [`c703bcb`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/c703bcb): rút gọn comment nguồn mã màu ANSI (Quý).
- [`faf925f`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/faf925f): in lời nhắc lựa chọn sau đường viền menu (Quý).
- [`dbce015`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/dbce015): hoàn thiện báo cáo tuần 3, đo lại benchmark Gray Code (Quý).

## 5. Phân công công việc

| Thành viên | MSSV | Công việc tuần 3 |
|---|---|---|
| Đào Nghiệm Minh | 25110042 | - Hoàn thiện giao diện CLI (tô màu, khung viền, lời nhắc nhập dữ liệu).<br>- Phân tích độ phức tạp của ba thuật toán.<br>- Xây dựng benchmark phiên bản đầu và đo Bảng 1, Bảng 2.<br>- Viết phần tổng quan, thiết kế CLI, độ phức tạp và benchmark trong báo cáo. |
| Nguyễn Võ Quang Quý | 25110055 | - Review mã nguồn benchmark, phát hiện lỗi phép đo Gray Code.<br>- Viết lại `benchmark.h` và đo lại Bảng 3.<br>- Kiểm thử và trace tay sinh hoán vị, sinh tổ hợp.<br>- Viết phần kiểm thử, tích hợp mã nguồn, khó khăn và bổ sung kế hoạch tuần 4. |
| Cả nhóm | | - Kiểm tra chéo mã nguồn và báo cáo.<br>- Nộp bài. |

## 6. Khó khăn và hướng giải quyết

- **Phép đo Gray Code bản đầu không đáng tin:** bản benchmark đầu gọi `verifyGray()` nhưng không dùng kết quả trả về. Trên máy 1 (g++ 12), phép đo ra khoảng 3,2 ns mỗi mã, nhưng con số này tính cả thời gian kiểm tra chứ không chỉ thời gian sinh mã. Trên máy 2 (g++ 16), trình biên dịch bỏ luôn vòng lặp khi tối ưu `-O2` nên phép đo ra 0 ms. Nhóm sửa bằng cách bỏ `verifyGray()` khỏi phép đo và XOR các mã Gray vào biến `grayXor` để vòng lặp không bị bỏ. Bản mới đo được khoảng 0,45 ns mỗi mã.
- **Chương trình bị crash trên máy 2:** máy lấy nhầm file `libstdc++-6.dll` cũ đi kèm Git. Biên dịch thêm cờ `-static` thì chương trình chạy bình thường.
- **Lời nhắc chọn menu nằm sai chỗ:** khi chạy thử để chụp ảnh minh chứng, nhóm thấy `-> Lua chon:` được in trước đường viền `====`, khiến người dùng phải gõ lựa chọn ở dòng bên dưới đường viền. Nhóm đổi lại thứ tự in để con trỏ đứng ngay sau `-> Lua chon:`.
- **Chưa làm phần giới hạn số cấu hình được in:** tuần này nhóm dồn thời gian sửa benchmark nên chưa kịp, phần này chuyển sang tuần 4.

## 7. Kế hoạch tuần 4

- Bổ sung tùy chọn chỉ in k cấu hình đầu tiên cho cả ba menu, đúng yêu cầu CLI của đề bài và kế hoạch từ tuần 2.
- Chạy lại toàn bộ benchmark trên máy 1 với `benchmark.h` mới, cập nhật `bench_results.csv` và ba bảng kết quả.
- Vẽ biểu đồ thời gian và ns/cấu hình từ `bench_results.csv`.
- Hoàn thiện báo cáo kỹ thuật và Self-Explanation cho từng yêu cầu của đề bài.
- Chuẩn bị cho phần vấn đáp đề tài.

## 8. Khai báo sử dụng AI và nguồn tài liệu tham khảo

### 8.1. Khai báo sử dụng AI và nguồn gốc kiến thức

Trong tuần 3, nhóm chủ yếu tự nghiên cứu tài liệu, hoàn thiện mã nguồn, chạy kiểm thử và thực hiện benchmark. Phần lớn kiến thức được nhóm tự tìm hiểu từ các nguồn tìm được qua công cụ tìm kiếm Google, được liệt kê ở mục 8.2.

Sau khi hoàn thành cài đặt, kiểm thử và benchmark, nhóm sử dụng `Gemini 3.8 Flash` để rà soát một số kiến thức kỹ thuật về #pragma once, inline, độ phức tạp của Gray Code và phương pháp đánh giá benchmark. AI được sử dụng để giải thích, đối chiếu và điều chỉnh một số nhận định kỹ thuật, không tham gia viết mã nguồn hay thay thế quá trình kiểm chứng của nhóm.

**Minh chứng:** [Cuộc trò chuyện với Gemini](https://share.gemini.google/RBkOQo69pslz).

### 8.2. Tài liệu tham khảo

**[1] Stack Overflow: List of ANSI color escape sequences**

[https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences](https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences)

Nội dung liên quan: Danh sách mã ANSI escape dùng để tô màu chữ trên terminal.

**[2] cppreference: std::chrono::steady_clock**

[https://en.cppreference.com/w/cpp/chrono/steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock)

Nội dung liên quan: Đồng hồ đo thời gian không bị ảnh hưởng khi chỉnh giờ hệ thống, dùng để đo thời gian chạy trong benchmark.

**[3] VNOI Wiki: Độ phức tạp thời gian**

[https://wiki.vnoi.info/algo/basic/computational-complexity](https://wiki.vnoi.info/algo/basic/computational-complexity)

Nội dung liên quan: Cách đánh giá độ phức tạp thời gian của thuật toán và ký hiệu Big-O.

**[4] Viblo: Cấu trúc dữ liệu và Giải thuật Bài 3: Độ phức tạp thời gian (Time Complexity) và Ký pháp Big-O**

[https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-3-do-phuc-tap-thoi-gian-time-complexity-va-ky-phap-big-o-1QLxnmjO4Aw](https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-3-do-phuc-tap-thoi-gian-time-complexity-va-ky-phap-big-o-1QLxnmjO4Aw)

Nội dung liên quan: Đánh giá thuật toán theo tốc độ tăng của số phép toán thay vì thời gian đo bằng giây, các cấp độ phức tạp thường gặp.

**[5] Viblo: Cấu trúc dữ liệu và Giải thuật Bài 8: Giới thiệu về Amortized Analysis (Phân tích khấu hao)**

[https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-8-gioi-thieu-ve-amortized-analysis-phan-tich-khau-hao-pPLkNbleJRZ](https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-8-gioi-thieu-ve-amortized-analysis-phan-tich-khau-hao-pPLkNbleJRZ)

Nội dung liên quan: Phân tích khấu hao, tính chi phí trung bình của một thao tác trong một chuỗi thao tác liên tiếp.

**[6] GeeksforGeeks: Measure execution time of a function in C++**

[https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/](https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/)

Nội dung liên quan: Đo thời gian chạy của một hàm bằng thư viện `<chrono>`, lấy thời điểm trước và sau khi chạy rồi tính hiệu.

**[7] USACO Guide: Time Complexity**

[https://usaco.guide/bronze/time-comp](https://usaco.guide/bronze/time-comp)

Nội dung liên quan: Ký hiệu Big-O, độ phức tạp của các vòng lặp, độ phức tạp O(2ⁿ) khi duyệt mọi tập con và O(n!) khi duyệt mọi hoán vị.

