# BÁO CÁO TIẾN ĐỘ (Tuần 4): Bổ sung và tối ưu chương trình

**Môn học:** Cấu trúc dữ liệu và Giải thuật.

**Mã lớp học phần:** DASA230179_Dot1, HK1 2026-2027.

**Giảng viên hướng dẫn:** Huỳnh Xuân Phụng.

**GitHub Repository:** https://github.com/QuangquyNguyenvo/DSA_final_project

## 1. Tổng quan

Sau tuần 3, chương trình đã có đủ ba thuật toán, menu và benchmark. Tuần 4 nhóm không thêm thuật toán mới mà tập trung bổ sung phần còn thiếu và hoàn thiện chương trình:

- Thêm tùy chọn chỉ in một số cấu hình đầu tiên cho cả ba menu (phần còn nợ từ tuần 3).
- Đo lại benchmark của cả ba thuật toán trên cùng một máy, rồi vẽ biểu đồ từ kết quả đo.
- Dọn mã nguồn: bỏ hàm cũ không còn dùng và tăng tốc phần in kết quả.
- Kiểm thử phần mới và chạy lại các test cũ sau khi sửa.
- Tổng kết lại các yêu cầu của đề bài (mục 8).
- Viết hướng dẫn biên dịch và chạy chương trình (mục 7).

**Minh chứng:**
![Kế hoạch tuần 3 và tuần 4 được viết tay trên Scrble](../img/week_4_planning.png)

## 2. Công việc thực hiện

### 2.1. Giới hạn số cấu hình được in

Tuần 3 chỉ chặn n để tránh in quá nhiều dòng, nhưng ở giới hạn trên chương trình vẫn in rất nhiều (hoán vị n = 10 ra khoảng 3,6 triệu dòng, Gray Code n = 30 ra hơn 1 tỉ dòng). Tuần này nhóm cho người dùng chọn số cấu hình muốn in ở cả ba menu, theo đúng yêu cầu CLI của đề bài.

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

Giới hạn n của từng menu vẫn giữ như tuần 3.

**Thay đổi trong mã nguồn:**

- Thêm hàm `readLimit()` để đọc `limit`. Nhập số âm hoặc nhập chữ thì báo lỗi và quay lại menu (xem mục 6).
- Hoán vị và tổ hợp: vòng `do ... while` vẫn chạy hết, chỉ gọi `print(a)` khi `limit == 0` hoặc `cnt < limit`.
- Gray Code: hàm `graycode()` tự in mã trong vòng lặp nên được thêm tham số `limit`. `benchmark.h` không gọi hàm này nên không phải sửa.

![Output menu 1 khi chỉ in 4 cấu hình đầu tiên](../img/week_4_perm_limit.png)

**Điều chỉnh giao diện:**

- Lời nhắc ban đầu dài 51 ký tự, tràn ra ngoài đường viền `----` (44 ký tự), nên được rút gọn còn `So cau hinh muon in (0 = tat ca): ` (34 ký tự).
- Các thông báo lỗi `Loi: ...` được tô đỏ (`\033[31m`), giống dòng `Kiem tra Gray Code: SAI`.

**Mã nguồn:**
- Hàm `readLimit`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L82-L93
- Hàm `graycode` có tham số `limit`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L48-L72
- Hàm `main`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L95-L181

### 2.2. Đo lại benchmark trên máy 1

Ở tuần 3, Bảng 1 và Bảng 2 đo trên máy 1 bằng bản benchmark đầu (`edbfebe`), còn Bảng 3 đo trên máy 2 bằng bản viết lại (`1a2a6f6`), nên ba bảng không so trực tiếp được. Tuần này nhóm đo lại cả ba thuật toán trong cùng một lần chạy, trên máy 1 với `benchmark.h` mới.

**Môi trường đo:** máy 1, giống mục 2.3.2 tuần 3.

| Thành phần | Máy 1 |
|---|---|
| CPU | Intel Core i7-11800H (11th Gen), 8 nhân / 16 luồng, 2.30 GHz |
| RAM | 8 GB |
| Trình biên dịch | g++ 12.1.0 (MinGW-W64 x86_64, posix-seh) |
| Cờ biên dịch | `g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen` |
| Bản benchmark | `benchmark.h` bản viết lại ([`1a2a6f6`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1a2a6f6/benchmark.h)) |

Cách đo và bộ dữ liệu giống mục 2.3.3 và 2.3.4 tuần 3 (1 lần khởi động, 5 lần đo, lấy median). Benchmark không in cấu hình nên phần giới hạn in không ảnh hưởng tới kết quả.

**Điều kiện chạy:** ở lần chạy đầu, số liệu Gray Code dao động từ 0,48 đến 0,62 ns mỗi mã (lý do ở mục 6). Nhóm chạy lại 3 lần, cả ba lần đều ra 0,46 đến 0,50 ns. Các bảng dưới đây lấy số liệu của lần đầu tiên trong 3 lần này.

**Bảng 4. Hoán vị (Algorithm L), máy 1**

| n | Số cấu hình (n!) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 8 | 40 320 | 0,1249 | 3,10 |  |  |
| 9 | 362 880 | 1,093 | 3,01 | 8,75 | 9 |
| 10 | 3 628 800 | 10,22 | 2,82 | 9,35 | 10 |
| 11 | 39 916 800 | 113,1 | 2,83 | 11,07 | 11 |
| 12 | 479 001 600 | 1 375 | 2,87 | 12,16 | 12 |

**Bảng 5. Tổ hợp chập k của n (k = n/2), máy 1**

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

**Bảng 6. Gray Code (chỉ sinh mã, không kiểm tra), máy 1**

| n | Số cấu hình (2ⁿ) | total_ms (median) | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 16 | 65 536 | 0,0309 | 0,47 |  |  |
| 18 | 262 144 | 0,1207 | 0,46 | 3,91 | 4 |
| 20 | 1 048 576 | 0,4852 | 0,46 | 4,02 | 4 |
| 22 | 4 194 304 | 1,934 | 0,46 | 3,98 | 4 |
| 24 | 16 777 216 | 7,75 | 0,46 | 4,01 | 4 |
| 26 | 67 108 864 | 32,49 | 0,48 | 4,19 | 4 |
| 28 | 268 435 456 | 128 | 0,48 | 3,94 | 4 |

Toàn bộ kết quả được lưu trong file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv). Ở bản hiện tại, file này và `bench_ns_per_item.csv` đã được chuyển vào thư mục [`results/`](../results/).

**Nhận xét:**

1. **Kết quả khớp với tuần 3:** hoán vị khoảng 2,8 đến 3,1 ns mỗi cấu hình, tổ hợp 2,6 đến 2,7 ns, Gray Code 0,46 đến 0,48 ns, gần như trùng với Bảng 1, 2, 3.
2. **Thời gian tăng đúng theo công thức:** cột tỉ lệ thời gian luôn gần cột tỉ lệ công thức, ví dụ hoán vị từ n = 11 lên 12 chậm đi 12,16 lần (công thức là 12).
3. **Mỗi mã Gray nhanh hơn khoảng 6 lần:** trong benchmark, mỗi mã Gray mất khoảng 0,47 ns, còn mỗi hoán vị hoặc tổ hợp mất 2,6 đến 3,1 ns. Benchmark Gray Code không gọi `verifyGray()` nên con số này không phản ánh trực tiếp tốc độ của menu 3.

### 2.3. Biểu đồ kết quả

Các biểu đồ được vẽ bằng Google Sheets từ file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv) ở mục 2.2:

- **Biểu đồ 1, 2, 3:** tổng thời gian sinh (`median_ms`) theo n, mỗi thuật toán một hình. Trục dọc dùng thang log vì thời gian tăng rất nhanh (hoán vị từ 0,12 ms lên 1 375 ms chỉ sau 4 lần tăng n).
- **Biểu đồ 4:** thời gian sinh một cấu hình (`ns_per_item`) của cả ba thuật toán trên cùng một hình, dữ liệu lấy từ [`bench_ns_per_item.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_ns_per_item.csv) (chỉ xếp lại cột `ns_per_item` cho dễ vẽ).

**Biểu đồ 1, 2, 3. Thời gian sinh theo n của hoán vị (Algorithm L), tổ hợp chập k của n (k = n/2) và Gray Code**

![Bảng bench_results.csv và biểu đồ thời gian sinh theo n của ba thuật toán](../img/week_4_chart_time_sheet.png)

**Biểu đồ 4. Thời gian sinh một cấu hình theo n**

![Bảng ns_per_item và biểu đồ thời gian sinh một cấu hình của ba thuật toán theo n](../img/week_4_chart_ns_sheet.png)

**Nhận xét:**

1. **Biểu đồ 1, 2, 3 gần như thẳng trên thang log:** thời gian tăng đúng theo số cấu hình. Gray Code tăng theo 2ⁿ, tổ hợp với k = n/2 tăng chậm hơn 2ⁿ một chút. Riêng đường hoán vị hơi cong lên, vì mỗi lần n tăng 1 thì số hoán vị nhân thêm n + 1, hệ số này lớn dần.
2. **Biểu đồ 4 gần như nằm ngang:** thời gian sinh một cấu hình gần như không đổi khi n tăng, đúng với O(1) khấu hao (mục 2.2 tuần 3).
3. **Biểu đồ 2 và 3 giống nhau chỉ là trùng hợp:** Gray Code nhiều cấu hình hơn khoảng 5 đến 7 lần nhưng mỗi cấu hình nhanh hơn khoảng 5,5 lần, nên tổng thời gian xấp xỉ nhau.

### 2.4. In tập con (subset) bên cạnh mã Gray

Đề bài yêu cầu sinh tập con (subset generation) bằng Gray Code, trong đó hai tập con liên tiếp khác nhau đúng một phần tử. Trước đây, chương trình chỉ in chuỗi bit như `{ 1 1 0 }`. Chuỗi bit đã biểu diễn một tập con, nhưng chưa hiển thị trực tiếp các phần tử được chọn.

Nhóm bổ sung phần in tập con thật của tập {1, 2, ..., n} ngay bên cạnh chuỗi bit. Các bit từ trái sang phải lần lượt ứng với phần tử 1 đến n, bit bằng 1 nghĩa là phần tử đó thuộc tập con. 

Ví dụ với n = 3:

Với `n = 3`, xét tập `S = {1, 2, 3}`. Ở mỗi bước, tính `G(i) = i ^ (i >> 1)`, viết mã thành 3 bit rồi chọn các phần tử ứng với bit `1`. Trong bảng, dấu ✓ nghĩa là chọn, dấu × nghĩa là không chọn. Ví dụ, `i = 2` cho `G(2) = 011`, tương ứng tập con `{2, 3}`. Bước tiếp theo là `010`, tương ứng `{2}`: chỉ bỏ phần tử `3`. Mã `000` biểu diễn tập rỗng `{}`.

![Bảng hand trace Gray Code sang tập con với n = 3 và S = {1, 2, 3}](../img/graycode_subset_hand_trace_manual.png)

Thay đổi chỉ nằm ở phần in trong `graycode()`. Trong code, `j` là chỉ số bit tính từ phải, bắt đầu từ `0`. Vòng lặp duyệt `j` từ `n-1` xuống `0`, tức duyệt các bit từ trái sang phải; nếu bit bằng `1` thì in phần tử tương ứng là `n-j`. Biến `first` dùng để ngăn cách các phần tử bằng dấu phẩy. Công thức `i ^ (i >> 1)`, thứ tự mã Gray, giới hạn in và phần kiểm tra `verifyGray()` vẫn giữ nguyên.

Cách hiển thị này làm rõ kết quả subset theo yêu cầu đề bài: người dùng vừa thấy mã bit, vừa thấy tập con tương ứng, và có thể đối chiếu trực tiếp việc mỗi bước chỉ thêm hoặc bỏ đúng một phần tử. Chương trình đã được biên dịch và chạy thử với n = 3 và n = 0 (tập rỗng), phần kiểm tra Gray Code đều trả về đúng.

**Minh chứng sau khi sửa:**

![Kết quả Gray Code n = 3: in chuỗi bit và tập con tương ứng](../img/graycode_subset_output.png)

### 2.5. Dọn mã nguồn và tăng tốc in kết quả

Nhóm đọc lại `comb_gen.cpp` và sửa thêm vài chỗ nhỏ:

- **Bỏ hàm `legacyNextGray`:** hàm sinh Gray Code cũ, đã không còn được gọi từ khi nhóm chuyển sang công thức `i ^ (i >> 1)`.
- **Tăng tốc phần in:** thêm `ios::sync_with_stdio(false);` ở đầu `main`. Lệnh này tắt đồng bộ giữa `cin`/`cout` với `printf`/`scanf` của C. Chương trình chỉ dùng `cin`/`cout` nên không bị ảnh hưởng gì.
- **Sửa chính tả:** `Greycode` thành `Gray Code` ở lời nhắc menu 3.

**Đo thời gian in:** nhóm cho cả hai bản in hết 10! hoán vị và 2²² mã Gray (khoảng 7,8 triệu dòng) ra file, mỗi bản chạy 2 lần trên máy 2 (g++ 16.2.0, `-O2 -static`).

| Bản | Lần 1 | Lần 2 |
|---|---|---|
| Trước khi sửa (`5d553d1`) | 11,98 s | 11,54 s |
| Sau khi sửa (`997cfa2`) | 5,71 s | 5,90 s |

Thời gian in giảm còn khoảng một nửa, còn output của hai bản giống hệt nhau (kiểm tra bằng lệnh `cmp`). Mỗi bản chỉ chạy 2 lần nên số liệu này dùng để minh họa, chưa đủ để kết luận cho mọi máy. Benchmark ở mục 2.2 không in nên không bị ảnh hưởng.

**Mã nguồn:** commit dọn mã nguồn: https://github.com/QuangquyNguyenvo/DSA_final_project/commit/997cfa2

## 3. Kiểm thử và kiểm chứng

### 3.1. Kiểm thử phần giới hạn số cấu hình được in

Các kết quả và ảnh trong phần này được ghi nhận trước khi bổ sung cách in subset ở mục 2.4; phiên bản hiện tại in thêm tập con bên cạnh chuỗi bit. Phép so sánh output sau khi dọn mã nguồn cũng thuộc thời điểm trước thay đổi hiển thị này.

Ở mỗi test, nhóm kiểm tra ba điều: chương trình in đúng `limit` cấu hình đầu, có `...` khi còn cấu hình chưa in, và `Tong so ...` vẫn là tổng thật. Mã test được đánh số tiếp theo tuần 3.

| Mã | Menu | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC25 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 2 | In 2 hoán vị đầu, có `...`, tổng 3! = 6 | `{1, 2, 3}`, `{1, 3, 2}`, `...`, `Tong so hoan vi: 6` | PASS |
| TC26 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 0 | In đủ 6 hoán vị như tuần 3, không có `...` | 6 hoán vị, `Tong so hoan vi: 6` | PASS |
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

![TC34: Gray Code n = 30, chỉ in 1 mã nhưng vẫn đếm và kiểm tra đủ 2³⁰ mã](../img/week_4_tc34_gray_n30.png)

---

TC36 lúc đầu không đạt: chương trình báo lỗi đúng nhưng sau đó thoát luôn, không quay lại menu. Nguyên nhân và cách sửa ở mục 6.

![TC36: nhập chữ ở lời nhắc số cấu hình, chương trình báo lỗi rồi quay lại menu](../img/week_4_tc36_invalid_limit.png)

---

### 3.2. Kiểm thử lại sau khi dọn mã nguồn

Sau khi dọn mã nguồn (mục 2.5), nhóm chạy lại TC10 đến TC36 và menu 4 (benchmark). Kết quả giống hệt trước khi sửa.

## 4. Tích hợp và quản lý mã nguồn

Phần giới hạn in, đo benchmark và vẽ biểu đồ được làm trên nhánh `week4` (PR #13). Phần review, sửa lỗi, dọn mã nguồn và hoàn thiện báo cáo được làm trên nhánh `review/week4` (PR #14).

**Mã nguồn:**
- Hàm `readLimit`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L82-L93
- Hàm `graycode` có tham số `limit`: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L48-L72
- Hàm `main` với lời nhắc `limit` ở cả ba menu: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/997cfa2/comb_gen.cpp#L95-L181
- File benchmark dùng để đo Bảng 4, 5, 6: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1a2a6f6/benchmark.h
- Kết quả benchmark: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv
- Dữ liệu vẽ Biểu đồ 4: https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_ns_per_item.csv

**Pull Request:**
- PR #13 (`week4`, Đào Nghiệm Minh): thêm giới hạn số cấu hình được in, đo lại benchmark trên máy 1 và vẽ biểu đồ: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/13
- PR #14 (`review/week4`, Nguyễn Võ Quang Quý): sửa lỗi nhập chữ ở `readLimit()`, dọn mã nguồn, bổ sung kiểm thử và hoàn thiện báo cáo tuần 4: https://github.com/QuangquyNguyenvo/DSA_final_project/pull/14

**Commit:**
- [`f4c36a7`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/f4c36a7): thêm tùy chọn giới hạn số cấu hình được in cho cả ba menu, tô đỏ thông báo lỗi (Minh).
- [`07548d7`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/07548d7): thêm báo cáo tuần 4, đo lại benchmark trên máy 1 và vẽ biểu đồ (Minh).
- [`5d553d1`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/5d553d1): sửa lỗi nhập chữ ở lời nhắc số cấu hình làm chương trình thoát (Quý).
- [`997cfa2`](https://github.com/QuangquyNguyenvo/DSA_final_project/commit/997cfa2): bỏ hàm `legacyNextGray`, tăng tốc phần in, sửa chính tả lời nhắc menu 3 và viết `cin.ignore` trong `readLimit()` gọn hơn (Quý).

## 5. Phân công công việc

| Thành viên | MSSV | Công việc tuần 4 |
|---|---|---|
| Đào Nghiệm Minh | 25110042 | - Thêm hàm `readLimit()` và giới hạn số cấu hình được in cho cả ba menu.<br>- Tô đỏ các thông báo lỗi nhập liệu.<br>- Đo lại benchmark trên máy 1 (Bảng 4, 5, 6), cập nhật `bench_results.csv`.<br>- Vẽ bốn biểu đồ bằng Google Sheets.<br>- Viết mục 2.1, 2.2, 2.3 và mục 7 trong báo cáo. |
| Nguyễn Võ Quang Quý | 25110055 | - Review mã nguồn tuần 4, phát hiện và sửa lỗi nhập chữ ở `readLimit()`.<br>- Dọn mã nguồn, tăng tốc phần in và đo thời gian in trước và sau khi sửa.<br>- Kiểm thử phần giới hạn in (TC25 đến TC36) và chạy lại các test cũ.<br>- Viết mục 2.5, mục 3 đến mục 6, mục 8 và mục 9 trong báo cáo. |
| Cả nhóm | | - Kiểm tra chéo mã nguồn và báo cáo.<br>- Chuẩn bị cho phần vấn đáp.<br>- Nộp bài. |

## 6. Khó khăn và hướng giải quyết

- **Nhập chữ ở lời nhắc số cấu hình làm chương trình thoát (TC36):** khi nhập chữ thay vì số, `cin` bị lỗi và phần chữ vẫn nằm lại trong luồng nhập, nên lần đọc lựa chọn menu tiếp theo cũng lỗi và chương trình thoát. Nhóm thêm `cin.clear()` để xóa lỗi và thử `cin.ignore()` để bỏ phần chữ, nhưng chương trình vẫn thoát, vì `cin.ignore()` không có tham số chỉ bỏ 1 ký tự: nhập `abc` thì vẫn còn sót `bc`. Nhóm đổi thành `cin.ignore(1000, '\n')` để bỏ phần còn lại của dòng vừa nhập sai, tối đa 1000 ký tự. Với cách nhập bình thường thì như vậy là đủ.
- **Số liệu Gray Code dao động ở lần đo đầu:** mỗi mã chỉ mất khoảng 0,5 ns nên số liệu dễ bị ảnh hưởng bởi các ứng dụng chạy nền. Ngoài ra, laptop chạy pin có thể tự hạ xung nhịp CPU để tiết kiệm điện. Nhóm đo lại khi máy đang cắm sạc và đã tắt bớt ứng dụng, chạy 3 lần liên tiếp thì cả ba lần đều cho kết quả gần như nhau.

## 7. Hướng dẫn biên dịch và chạy chương trình

Chương trình được viết bằng C++17, sử dụng trình biên dịch G++. Hai file `comb_gen.cpp` và `benchmark.h` cần nằm cùng một thư mục.

Biên dịch:

```bash
g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen
```

Nếu chương trình bị crash trên Windows do lỗi file `.dll`, thêm cờ `-static` khi biên dịch (xem tuần 3 mục 6).

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

## 8. Tổng kết: đối chiếu yêu cầu đề bài

Tuần 4 là tuần cuối, nên nhóm tổng hợp lại từng yêu cầu của đề bài: đã làm như thế nào (Self-Explanation) và xem chi tiết ở đâu.

| Yêu cầu đề bài | Tự giải thích | Chi tiết |
|---|---|---|
| 1. Sinh hoán vị bằng Algorithm L | Tìm pivot là vị trí phải nhất có a[i] < a[i+1], đổi chỗ với phần tử phải nhất lớn hơn nó, rồi đảo đoạn phía sau để được hoán vị kế tiếp nhỏ nhất. Dãy giảm dần thì dừng. | Tuần 1 mục 2.2<br>Tuần 3 mục 3.1 |
| 2. Sinh tổ hợp chập k của n theo thứ tự từ điển | Tìm vị trí phải nhất chưa đạt giá trị tối đa n − k + i + 1, tăng nó lên 1 rồi đặt phần phía sau thành dãy tăng liên tiếp. Mọi vị trí đều đạt tối đa thì dừng. | Tuần 1 mục 2.3<br>Tuần 3 mục 3.1 |
| 3. Sinh tập con bằng Gray Code | Mã thứ i là `i ^ (i >> 1)`. Bit thứ j bằng 1 nghĩa là phần tử j có trong tập con. | Tuần 2 mục 2.3 |
| 4. Với n ≥ 10, số cấu hình khớp n!, C(n, k), 2ⁿ | Chương trình đếm mọi cấu hình đã sinh và in dòng `Tong so ...` để đối chiếu với công thức.<br>Benchmark đếm đúng tới 12!, C(30, 15) và 2²⁸. | Tuần 2 mục 3.4<br>Tuần 3 mục 3.3 |
| 5. Vì sao hai tập con Gray Code liên tiếp chỉ khác nhau đúng một phần tử | `i ^ (i+1)` là một dãy bit 1 liên tiếp ở cuối. XOR dãy đó với chính nó dịch phải 1 bit thì chỉ còn đúng một bit 1.<br>`verifyGray()` kiểm tra lại điều này bằng `__builtin_popcount(diff) == 1`. | Tuần 2 mục 3.3 |
| Độ phức tạp: thời gian sinh mỗi cấu hình và tổng thời gian | - Sinh mỗi cấu hình: hoán vị các phần tử khác nhau là O(1) khấu hao. Tổ hợp là O(k) trong trường hợp xấu nhất, O(1) khấu hao khi k ≤ n/2. Gray Code là O(1) mỗi bước.<br>- Tổng thời gian khi in: O(n · n!), O(k · C(n, k)) và O(n · 2ⁿ).<br>- Đo thực tế: khoảng 2,6 đến 3,1 ns mỗi hoán vị hoặc tổ hợp, 0,47 ns mỗi mã Gray. | Tuần 3 mục 2.2, 2.3<br>Tuần 4 mục 2.2, 2.3 |
| Test tối thiểu | - Trace tay: hoán vị n = 3, tổ hợp n = 5, k = 3 (TC10, TC18 tuần 3) và Gray Code n = 4 (tuần 2 mục 3.5).<br>- Dữ liệu lớn: 10!, C(20, 10), 2³⁰ (TC15, TC21 tuần 3; TC34 tuần 4) và benchmark.<br>- Trường hợp biên: n = 0, k = 0, k = n, phần tử trùng, nhập sai (TC01 tuần 2; TC11 đến TC14, TC19, TC20 tuần 3; TC33, TC36 tuần 4). | Mục 3 của tuần 2, 3, 4 |
| CLI in k cấu hình đầu | Sau khi nhập thông số, chương trình hỏi số cấu hình muốn in. Thuật toán vẫn sinh và đếm đủ mọi cấu hình. | Tuần 4 mục 2.1 |
| Hướng dẫn biên dịch và chạy | `g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen`, thêm `-static` nếu gặp lỗi dll trên Windows. | Tuần 1 mục 2.4<br>Tuần 4 mục 7 |
| Khai báo sử dụng AI | Ghi ở mục khai báo AI của từng tuần. | Tuần 1 mục 7<br>Tuần 2, 3 mục 8<br>Tuần 4 mục 9 |

## 9. Khai báo sử dụng AI và nguồn tài liệu tham khảo

### 9.1. Khai báo sử dụng AI và nguồn gốc kiến thức

Trong tuần 4, nhóm chủ yếu tối ưu chương trình và hoàn thiện các phần còn thiếu từ những tuần trước, thay vì nghiên cứu thêm thuật toán mới. Các công việc được thực hiện dựa trên kiến thức đã tìm hiểu và mã nguồn đã xây dựng.

Nhóm sử dụng công cụ tìm kiếm để tra cứu cách dùng một số hàm và thiết lập nhập xuất trong C++, cụ thể là `cin.clear()`, `cin.ignore()` để xử lý dữ liệu nhập sai và `ios::sync_with_stdio(false)` để tăng tốc nhập xuất. Các tài liệu tham khảo được liệt kê tại mục 9.2.

### 9.2. Tài liệu tham khảo

**[1] GeeksforGeeks: How to Handle Wrong Data Type Input in C++?**

[https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/](https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/)

Nội dung liên quan: Xử lý khi người dùng nhập sai kiểu dữ liệu, dùng `cin.clear()` để xóa trạng thái lỗi của `cin` và `cin.ignore()` để bỏ phần nhập sai còn lại.

**[2] GeeksforGeeks: Fast I/O for Competitive Programming**

[https://www.geeksforgeeks.org/dsa/fast-io-for-competitive-programming/](https://www.geeksforgeeks.org/dsa/fast-io-for-competitive-programming/)

Nội dung liên quan: Tăng tốc nhập xuất bằng `ios_base::sync_with_stdio(false)`, tắt đồng bộ giữa luồng nhập xuất của C++ và C.

**[3] Viblo: Các kĩ năng thi cử 10.1: Kĩ thuật tối ưu tốc độ chương trình C++**

[https://viblo.asia/p/cac-ki-nang-thi-cu-101-ki-thuat-toi-uu-toc-do-chuong-trinh-c-Yym40njjL91](https://viblo.asia/p/cac-ki-nang-thi-cu-101-ki-thuat-toi-uu-toc-do-chuong-trinh-c-Yym40njjL91)

Nội dung liên quan: Giải thích vì sao tắt đồng bộ giữa `cin`, `cout` với luồng chuẩn của C giúp chương trình nhập xuất nhanh hơn.
