# BÁO CÁO DỰ ÁN

Đề tài: Combinatorial Generation: Permutations, Combinations, and Subsets

Môn học: Cấu trúc dữ liệu và Giải thuật.

Mã lớp học phần: DASA230179_Dot1, HK1 2026-2027.

Giảng viên hướng dẫn: Huỳnh Xuân Phụng.

Thành viên nhóm:

| Họ và tên | MSSV |
|---|---|
| Nguyễn Võ Quang Quý | 25110055 |
| Đào Nghiệm Minh | 25110042 |

GitHub Repository: https://github.com/QuangquyNguyenvo/DSA_final_project

## 1. Tổng quan

Trong dự án này, nhóm tìm hiểu và cài đặt ba thuật toán sinh hoán vị, tổ hợp và tập con. Nội dung dựa trên chương 7.2.1, Generating Combinatorial Patterns, trong The Art of Computer Programming, Vol. 4A.

Chương trình được viết bằng C++17 và sử dụng giao diện dòng lệnh CLI. Nhóm kiểm tra kết quả sinh ra, đếm số cấu hình và đo thời gian chạy để so sánh với phần phân tích độ phức tạp.

### 1.1. Yêu cầu đề bài

- Cài đặt Algorithm L để sinh hoán vị theo thứ tự từ điển.
- Sinh tổ hợp chập k của n theo thứ tự từ điển.
- Sinh tập con bằng Gray Code. Hai tập con liên tiếp khác nhau đúng một phần tử.
- Kiểm chứng số cấu hình với n đến ít nhất 10, đối chiếu n!, C(n, k) và 2ⁿ.
- Giải thích tính chất khác nhau đúng một phần tử của bộ sinh tập con.
- Phân tích thời gian sinh mỗi cấu hình và tổng thời gian sinh.
- Có ví dụ trace tay, dữ liệu lớn và trường hợp biên.
- Cung cấp CLI cho phép in một số cấu hình đầu tiên của cả ba dãy.

Báo cáo trình bày cách hoạt động của ba thuật toán, kết quả kiểm thử và thời gian chạy. Số liệu và ảnh được lấy từ báo cáo [tuần 1](reports/week1.md), [tuần 2](reports/week2.md), [tuần 3](reports/week3.md) và [tuần 4](reports/week4.md). Nhóm dùng lại các kết quả đã ghi nhận trong bốn tuần.

## 2. Thiết kế chương trình và cách sử dụng

### 2.1. Cấu trúc mã nguồn

Chương trình chia thành phần sinh cấu hình trong `comb_gen.cpp` và phần đo thời gian trong `benchmark.h`. Các file kết quả, ảnh minh chứng và báo cáo được lưu riêng như sau:

| Thành phần | Chức năng |
|---|---|
| `comb_gen.cpp` | Ba thuật toán sinh, kiểm tra Gray Code, nhập liệu, in cấu hình và menu |
| `benchmark.h` | Tính số cấu hình theo công thức, đo thời gian và ghi CSV |
| `results/bench_results.csv` | Dữ liệu benchmark do menu 4 xuất ra |
| `results/bench_ns_per_item.csv` | Dữ liệu sắp xếp lại để vẽ biểu đồ thời gian mỗi cấu hình |
| `results/count_verification.csv` | Kết quả kiểm chứng toàn bộ với n từ 0 đến 10 |
| `results/report_case_regression.csv` | Kết quả chạy lại TC10 đến TC42 trên bản hiện tại |
| `results/bench_combination_k.csv` | Kết quả đo tổ hợp với n cố định và k thay đổi |
| `img/` | Ảnh minh chứng kế hoạch, trace tay, kiểm thử và biểu đồ |
| `README.md` | Báo cáo cuối cùng của dự án |
| `reports/week1.md` đến `reports/week4.md` | Báo cáo tiến độ theo tuần |

Benchmark gọi trực tiếp `nextPermutation()` và `nextCombination()` của chương trình. Gray Code dùng cùng công thức XOR. Việc kiểm tra mã Gray và hiển thị tập con được thực hiện tại menu 3.

### 2.2. Biên dịch và chạy chương trình

Chương trình được viết bằng C++17, sử dụng trình biên dịch G++. Hai file `comb_gen.cpp` và `benchmark.h` cần nằm cùng một thư mục.

Biên dịch:

```bash
g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen
```

Nếu chương trình bị lỗi hoặc crash trên Windows, kể cả khi không báo thiếu file `.dll`, có thể thử thêm cờ `-static` khi biên dịch. Cách này đã giúp nhóm xử lý trường hợp chương trình lấy nhầm file DLL cũ trên máy 2.

Chạy trên Windows PowerShell:

```powershell
.\comb_gen.exe
```

Chạy trên Linux:

```bash
./comb_gen
```

### 2.3. Menu và giới hạn in kết quả

Chương trình có ba lựa chọn sinh cấu hình, một lựa chọn benchmark và lựa chọn `0` để thoát:

| Menu | Dữ liệu nhập theo thứ tự | Giới hạn đầu vào |
|---|---|---|
| 1. Sinh hoán vị | n, n phần tử, `limit` | 0 ≤ n ≤ 20 |
| 2. Sinh tổ hợp | n, k, `limit` | 0 ≤ k ≤ n ≤ 20 |
| 3. Sinh tập con bằng Gray Code | n, `limit` | 0 ≤ n ≤ 30 |
| 4. Benchmark | Không cần nhập thêm | Dùng bộ dữ liệu cố định ở mục 6 |

Ở menu 1 đến 3, sau khi nhập dữ liệu, người dùng nhập số cấu hình muốn in tại lời nhắc `So cau hinh muon in (0 = tat ca):`. Trong mã nguồn, giá trị này được đặt tên là `limit` để phân biệt với k của tổ hợp chập k.

- `limit = 0`: in tất cả khi tổng không quá 3.628.800 cấu hình, bằng 10!. Nếu vượt ngưỡng này, cả ba menu đều từ chối và yêu cầu nhập `limit` lớn hơn 0. Với hoán vị, tổng đã tính đến các phần tử trùng nên n lớn vẫn được in hết nếu số hoán vị phân biệt nhỏ.
- `limit > 0`: in tối đa `limit` cấu hình đầu tiên. Có thêm `...` nếu còn cấu hình chưa in.
- Khi đủ `limit`, chương trình dừng sinh và in số cấu hình đã sinh qua dòng `Da sinh`. Tổng số cấu hình được tính riêng từ công thức. Với hoán vị có phần tử trùng, tổng được chia cho giai thừa số lần xuất hiện của từng giá trị.
- Với Gray Code, nếu chỉ sinh một phần dãy thì chương trình chỉ kiểm tra tính chất một bit trên phần đã sinh. Khi sinh hết, chương trình kiểm tra thêm phạm vi và mã trùng bằng `verifyGray()`.

Ví dụ, hoán vị n = 20 với `limit = 2` chỉ sinh hai hoán vị rồi quay lại menu. Dòng tổng vẫn hiển thị 20! theo công thức. Giới hạn n = 20 giúp tổng số hoán vị không vượt kiểu `long long`.

Ảnh dưới được ghi nhận ở bản chỉ giới hạn in. Bản hiện tại dừng sinh sớm và tách số đã sinh khỏi tổng theo công thức.

![Output menu 1 khi chỉ in 4 cấu hình đầu tiên](img/week_4_perm_limit.png)

Hàm `readNumber()` xử lý trường hợp nhập chữ ở n, k và các phần tử của hoán vị. Hàm `readLimit()` kiểm tra thêm điều kiện `limit` không âm. Khi nhập sai ở các ô này, chương trình báo lỗi và quay lại menu. Các thông báo lỗi được tô đỏ để dễ nhận biết. Nếu nhập chữ ngay tại lựa chọn menu chính, chương trình kết thúc.

Menu 4 ghi kết quả vào `results/bench_results.csv`. Cần chạy chương trình ở thư mục gốc của repo và bảo đảm thư mục `results/` đã tồn tại. Mỗi lần chạy sẽ ghi lại file này. `bench_ns_per_item.csv` được sắp xếp riêng để vẽ biểu đồ, không do menu 4 tự tạo.

## 3. Các thuật toán và ví dụ minh họa

### 3.1. Sinh hoán vị bằng Algorithm L

Nhóm dùng Algorithm L để sinh lần lượt các hoán vị theo thứ tự từ điển, bắt đầu từ dãy đã sắp xếp tăng dần.

Mỗi bước tìm vị trí phải nhất còn có thể tăng, gọi là pivot. Sau khi đổi phần tử tại đó với một phần tử lớn hơn, thuật toán đảo đoạn phía sau để tạo hoán vị kế tiếp theo thứ tự từ điển.

Các bước chính:

- Tìm pivot i là vị trí phải nhất có a[i] < a[i+1]. Nếu không có, dãy đã giảm dần và thuật toán dừng.
- Tìm phần tử phải nhất lớn hơn a[i], rồi đổi chỗ phần tử đó với a[i].
- Đảo đoạn sau i về thứ tự tăng dần để được hoán vị kế tiếp nhỏ nhất.

#### Ví dụ trace tay

Với n = 3 và đầu vào {3, 1, 2}, chương trình sắp xếp lại thành {1, 2, 3}. Bảng dưới ghi từng bước đổi chỗ và đảo đoạn đuôi. Chỉ số i và j bắt đầu từ 0.

| Bước | Dãy hiện tại | Pivot i | j | Sau khi đổi chỗ | Sau khi đảo đoạn sau i |
|---|---|---|---|---|---|
| 1 | {1, 2, 3} | 1 vì 2 < 3 | 2 | {1, 3, 2} | {1, 3, 2} |
| 2 | {1, 3, 2} | 0 vì 1 < 3 | 2 | {2, 3, 1} | {2, 1, 3} |
| 3 | {2, 1, 3} | 1 vì 1 < 3 | 2 | {2, 3, 1} | {2, 3, 1} |
| 4 | {2, 3, 1} | 0 vì 2 < 3 | 1 | {3, 2, 1} | {3, 1, 2} |
| 5 | {3, 1, 2} | 1 vì 1 < 2 | 2 | {3, 2, 1} | {3, 2, 1} |
| 6 | {3, 2, 1} | không có | | | Dừng, trả về `false` |

Với `limit = 0`, chương trình in `{1, 2, 3}`, `{1, 3, 2}`, `{2, 1, 3}`, `{2, 3, 1}`, `{3, 1, 2}`, `{3, 2, 1}`, rồi báo `Da sinh: 6` và `Tong so hoan vi theo cong thuc: 6`. Thứ tự trùng với bảng trace tay. Ảnh dưới được chụp ở bản cũ nên dòng tổng có cách ghi khác.

![Output chương trình khi chọn menu 1 với n = 3, nhập 3 1 2](img/week_3_perm_n3.png)

### 3.2. Sinh tổ hợp theo thứ tự từ điển

Với tổ hợp chập k của n, nhóm biểu diễn các phần tử được chọn bằng một dãy tăng dần và sinh theo thứ tự từ điển. Thuật toán tìm vị trí ngoài cùng bên phải chưa đạt giới hạn, tăng phần tử tại vị trí đó và đặt các phần tử phía sau về giá trị nhỏ nhất hợp lệ.

Các bước chính:

- Khởi tạo tổ hợp đầu tiên {1, 2, ..., k}.
- Tìm vị trí i phải nhất còn nhỏ hơn giới hạn n - k + i + 1, với chỉ số bắt đầu từ 0.
- Tăng a[i] lên 1 và đặt phần đuôi thành dãy tăng liên tiếp nhỏ nhất có thể.
- Dừng khi mọi vị trí đều đạt giới hạn. Trường hợp k = 0 có một tổ hợp rỗng. k > n bị từ chối ngay khi nhập.

#### Ví dụ trace tay

Với n = 5 và k = 3, giới hạn của ba vị trí lần lượt là 3, 4, 5. Chỉ số i bắt đầu từ 0. Mỗi bước tăng vị trí phải nhất chưa đạt giới hạn rồi đặt lại đoạn đuôi.

| Bước | Tổ hợp hiện tại | Vị trí i | Tổ hợp kế tiếp |
|---|---|---|---|
| 1 | {1, 2, 3} | 2 | {1, 2, 4} |
| 2 | {1, 2, 4} | 2 | {1, 2, 5} |
| 3 | {1, 2, 5} | 1 vì a[2] đã đạt 5 | {1, 3, 4} |
| 4 | {1, 3, 4} | 2 | {1, 3, 5} |
| 5 | {1, 3, 5} | 1 | {1, 4, 5} |
| 6 | {1, 4, 5} | 0 vì a[1] đã đạt 4 và a[2] đã đạt 5 | {2, 3, 4} |
| 7 | {2, 3, 4} | 2 | {2, 3, 5} |
| 8 | {2, 3, 5} | 1 | {2, 4, 5} |
| 9 | {2, 4, 5} | 0 | {3, 4, 5} |
| 10 | {3, 4, 5} | không có | Dừng, trả về `false` |

Với `limit = 0`, chương trình in đúng 10 tổ hợp theo thứ tự trên, rồi báo `Da sinh: 10` và `Tong so to hop theo cong thuc: 10`. Kết quả khớp C(5, 3) = 10. Ảnh dưới được chụp ở bản cũ nên dòng tổng có cách ghi khác.

![Output chương trình khi chọn menu 2 với n = 5, k = 3](img/week_3_comb_5_3.png)

### 3.3. Sinh tập con bằng Gray Code

Mỗi tập con của {1, 2, ..., n} được biểu diễn bằng một chuỗi n bit. Bit bằng 1 nghĩa là phần tử tương ứng được chọn. Có 2ⁿ chuỗi bit tương ứng với 2ⁿ tập con, bao gồm tập rỗng.

Chương trình sử dụng Binary Reflected Gray Code:

```cpp
int gray = i ^ (i >> 1);
```

Khi sinh toàn bộ, chỉ số i chạy từ 0 đến 2ⁿ − 1. Mỗi mã được đưa qua `verifyGray()` để kiểm tra phạm vi, phát hiện trùng bằng mảng `seen` và kiểm tra XOR với mã trước có đúng một bit 1. Hàm nhận đúng giá trị vừa sinh, không tự sinh lại một dãy mã độc lập. Khi có `limit` nhỏ hơn tổng, vòng lặp dừng sớm và chỉ kiểm tra tính chất một bit trên các mã đã sinh, không cấp phát mảng `seen` cho toàn bộ dãy.

#### Vì sao hai tập con liên tiếp chỉ khác một phần tử?

Hai mã Gray liên tiếp luôn khác nhau đúng một bit, tức là mỗi bước chỉ thêm hoặc bớt đúng một phần tử khỏi tập con hiện tại.

Xét hai chỉ số liên tiếp i và i + 1, gọi k là số bit 1 liên tiếp ở cuối của i. Khi cộng 1, k bit 1 này chuyển thành 0 và bit 0 ngay trước đó chuyển thành 1, nên `i ^ (i+1)` là một dãy (k+1) bit 1 liên tiếp ở cuối. Khi đó:

 G(i) ^ G(i+1) = (i ^ (i+1)) ^ ((i ^ (i+1)) >> 1)

Hai dãy bit 1 này lệch nhau một vị trí nên triệt tiêu nhau, chỉ còn lại đúng một bit 1.

Ví dụ với i = 3, i + 1 = 4:

- i ^ (i+1) = 011 ^ 100 = 111
- 111 ^ (111 >> 1) = 111 ^ 011 = 100, chỉ khác đúng một bit.
- Kiểm tra: G(3) = 010, G(4) = 110.

Đây cũng chính là điều kiện mà hàm `verifyGray()` kiểm tra bằng `__builtin_popcount(diff) == 1`.

#### Biểu diễn tập con và ví dụ trace tay

Chương trình in cả chuỗi bit và tập con tương ứng của S = {1, 2, ..., n}. Các bit từ trái sang phải lần lượt ứng với phần tử 1 đến n. Bit bằng 1 nghĩa là chọn phần tử đó.

Với n = 3, mã `011` biểu diễn tập con `{2, 3}`, còn mã kế tiếp `010` biểu diễn `{2}`. Bước chuyển này chỉ bỏ phần tử 3. Mã `000` biểu diễn tập rỗng `{}`. Bảng dưới đây trình bày đủ 8 trường hợp. Dấu ✓ nghĩa là chọn, dấu × nghĩa là không chọn.

![Bảng hand trace Gray Code sang tập con với n = 3 và S = {1, 2, 3}](img/graycode_subset_hand_trace_manual.png)

Trong `graycode()`, vòng lặp duyệt chỉ số bit `j` từ `n-1` xuống `0`. Nếu bit bằng 1, chương trình in phần tử `n-j`. Cách ánh xạ này thống nhất với thứ tự bit từ trái sang phải trong bảng.

![Kết quả Gray Code n = 3: in chuỗi bit và tập con tương ứng](img/graycode_subset_output.png)

#### Gray Code n = 4

Nhóm trace tay trường hợp n = 4 bằng công thức `G(i) = i ^ (i >> 1)` rồi đối chiếu với output của chương trình.

![Bảng trace tay Gray Code với n = 4](img/week_2_trace_gray_n4.png)

![Output chương trình khi chọn menu 3 với n = 4](img/week_2_output_gray_n4.png)

Cả 16 mã trong bảng trace tay trùng khớp với output theo đúng thứ tự. Từ bảng trên có thể thấy thêm hai tính chất:

- Với i từ 8 đến 15, thứ tự 3 bit cuối là thứ tự của 8 mã đầu đọc ngược lại. Bit đầu chuyển từ 0 thành 1.
- Trong 15 bước chuyển, các bit từ trái sang phải lần lượt lật 1, 2, 4 và 8 lần. Vì vậy, bit ứng với phần tử 1 lật 1 lần, còn bit ngoài cùng bên phải ứng với phần tử 4 lật 8 lần. Phần sinh mã trực tiếp bằng XOR có chi phí O(1) mỗi bước.

Các hàm `nextPermutation()`, `nextCombination()`, `graycode()` và `verifyGray()` nằm trong [`comb_gen.cpp`](comb_gen.cpp).

## 4. Phân tích độ phức tạp

Thời gian chạy gồm thời gian sinh cấu hình và thời gian in. Riêng Gray Code còn có thời gian kiểm tra kết quả. Vì vậy, nhóm phân tích riêng phần sinh và phần in từng cấu hình.

| Thuật toán | Số cấu hình | Chi phí sinh mỗi bước | Tổng thời gian khi in tất cả | Bộ nhớ |
|---|---|---|---|---|
| Hoán vị với phần tử khác nhau | n! | O(n) xấu nhất, O(1) khấu hao | O(n · n!) | O(n) |
| Tổ hợp | C(n, k) | O(k) xấu nhất, O(1) khấu hao khi k ≤ n/2 | O(k · C(n, k)) với k ≥ 1 | O(k) |
| Gray Code | 2ⁿ | O(1) cho công thức sinh mã | O(n · 2ⁿ) với n ≥ 1 | O(2ⁿ) khi kiểm tra bằng seen |

Hoán vị có thể tốn O(n) cho một bước nếu phải duyệt và đảo đoạn đuôi dài. Nhưng phần lớn các bước chỉ xử lý vài phần tử cuối.

Với các phần tử khác nhau, trong L! cách sắp xếp L phần tử cuối chỉ có một cách giảm dần. Do đó, tỉ lệ hoán vị có đuôi giảm dần dài ít nhất L là 1/L!. Khi L tăng, tỉ lệ này giảm từ 1 xuống 1/2, 1/6, 1/24 và tiếp tục giảm. Tổng 1 + 1/2 + 1/6 + ... nhỏ hơn 2, nên độ dài đuôi trung bình bị chặn bởi một hằng số. Vì mỗi bước tốn thời gian theo độ dài đuôi, chi phí sinh là O(1) khấu hao.

Tổng phần sinh không in là O(n!), cộng thêm O(n log n) cho lần sắp xếp ban đầu. Nếu phần tử trùng nhau, số hoán vị phân biệt là n! / (m₁! · m₂! · ...), trong đó mᵢ là số lần xuất hiện của mỗi giá trị. Lập luận O(1) khấu hao ở trên chỉ áp dụng cho các phần tử khác nhau.

Tổ hợp có thể tốn O(k) cho một bước khi phải tìm vị trí cần tăng và đặt lại đoạn đuôi. Nếu có r phần tử cuối đã đạt giới hạn, bước đó tốn O(r + 1).

Tỉ lệ tổ hợp có ít nhất r phần tử cuối đã đạt giới hạn là C(n-r, k-r) / C(n, k). Khi k ≤ n/2, tỉ lệ này không quá 1/2ʳ. Nghĩa là tỉ lệ phải lùi qua ít nhất 1, 2, 3 phần tử lần lượt không quá 1/2, 1/4, 1/8. Tổng các tỉ lệ không quá 1, nên số phần tử phải lùi qua trung bình cũng không quá 1. Vì vậy, chi phí sinh là O(1) khấu hao khi k ≤ n/2.

Tính trên toàn bộ dãy, kể cả lần kiểm tra dừng cuối cùng, số phần tử đã đạt giới hạn ở đuôi trung bình là k/(n-k+1). k > n/2 không có nghĩa là chi phí luôn tăng theo n. Điều này phụ thuộc k gần n đến mức nào. Chẳng hạn, với k = n-1, giá trị trung bình là (n-1)/2 nên không còn bị chặn bởi một hằng số.

Tổng phần sinh không in là O(C(n, k)) trong phạm vi trên, cộng thêm O(k) để khởi tạo tổ hợp đầu. Mỗi cấu hình cần O(k) để in. Với k > n/2, báo cáo chỉ dùng cận O(k) cho một bước và O(k · C(n, k)) cho toàn bộ phần sinh. Trường hợp k = 0 chỉ có một tổ hợp rỗng.

Gray Code: XOR và dịch bit tốn O(1) trên kiểu số nguyên đang dùng. Nếu chỉ sinh mã và không in, tổng thời gian là O(2ⁿ). In bit và duyệt để in tập con đều tốn O(n), nên tổng thời gian khi in hết là O(n · 2ⁿ) với n ≥ 1. Mảng seen dùng O(2ⁿ) bộ nhớ phục vụ kiểm chứng. Nếu chỉ sinh mã thì bộ nhớ phụ O(1). Trường hợp n = 0 có một tập rỗng.

Với `limit > 0`, CLI chỉ sinh tối đa `limit` cấu hình nên thời gian phụ thuộc phần dãy cần in. Các phân tích tổng thời gian phía trên áp dụng khi sinh toàn bộ. Riêng Gray Code chỉ cần O(1) bộ nhớ phụ khi sinh một phần dãy, còn kiểm tra toàn bộ bằng `seen` cần O(2ⁿ).

## 5. Kiểm thử và kiểm chứng

Nhóm kiểm tra thứ tự sinh bằng các bảng trace ở mục 3, kiểm tra số lượng bằng công thức và thử thêm đầu vào biên, đầu vào sai. TC10 đến TC42 đã được chạy lại trên bản hiện tại, các bảng dưới ghi kết quả mới. Ảnh minh chứng giữ từ các lần kiểm thử trước nên có thể khác cách ghi dòng tổng. TC17 đổi từ n = 11 sang n = 21 để tiếp tục kiểm tra đầu vào vượt giới hạn mới.

TC10 đến TC36 giữ mã của tuần 3 và tuần 4 để tiện đối chiếu ảnh minh chứng. Sáu test số lượng từ tuần 2 được đổi thành TC37 đến TC42 trong báo cáo cuối để tránh trùng mã. Một số ảnh Gray Code cũ chỉ có chuỗi bit. Bản hiện tại in thêm tập con tương ứng.

Các trường hợp sinh không ghi `limit` trong bảng đều dùng `limit = 0` để sinh toàn bộ.

### 5.1. Kiểm thử hoán vị, tổ hợp và menu chính

Sinh hoán vị ở menu 1:

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC10 | Cơ bản, đối chiếu trace tay | n = 3, {3, 1, 2} | 3! = 6 hoán vị theo thứ tự từ điển | `Da sinh: 6`, `Tong so hoan vi theo cong thuc: 6` | PASS |
| TC11 | Biên n = 0 | n = 0 | 1 hoán vị rỗng | `{}`. `Da sinh: 1`, `Tong so hoan vi theo cong thuc: 1` | PASS |
| TC12 | Một phần tử | n = 1, {7} | 1 hoán vị | `{7}`. `Da sinh: 1`, `Tong so hoan vi theo cong thuc: 1` | PASS |
| TC13 | Có phần tử trùng | n = 3, {1, 1, 2} | 3!/2! = 3 hoán vị, không lặp lại | `{1, 1, 2}`. Dòng cuối `{2, 1, 1}`. `Da sinh: 3`, `Tong so hoan vi theo cong thuc: 3` | PASS |
| TC14 | Tất cả phần tử trùng | n = 3, {2, 2, 2} | 1 hoán vị | `{2, 2, 2}`. `Da sinh: 1`, `Tong so hoan vi theo cong thuc: 1` | PASS |
| TC15 | Dữ liệu lớn, sinh toàn bộ | n = 10, {1, ..., 10} | 10! = 3 628 800 hoán vị, kết thúc ở dãy giảm dần | Dòng cuối `{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}`. `Da sinh: 3628800`, `Tong so hoan vi theo cong thuc: 3628800` | PASS |
| TC16 | Nhập n âm | n = -1 | Báo lỗi và quay lại menu | `Loi: n phai thoa 0 <= n <= 20` | PASS |
| TC17 | Vượt giới hạn | n = 21 | Báo lỗi và quay lại menu | `Loi: n phai thoa 0 <= n <= 20` | PASS |

Ở TC13 và TC14, chương trình không in hoán vị nào bị lặp lại là nhờ dấu `>=` khi tìm pivot và `<=` khi tìm phần tử thay thế. Pivot chỉ được đổi với một phần tử lớn hơn nó, rồi phần đuôi được đảo để tạo hoán vị kế tiếp theo thứ tự từ điển. Vì mỗi bước đều tăng thứ tự từ điển, chương trình không sinh lại hoán vị đã xuất hiện.

![TC13: hoán vị có phần tử trùng {1, 1, 2}](img/week_3_perm_duplicate.png)

![TC14: hoán vị tất cả phần tử trùng {2, 2, 2}](img/week_3_perm_all_same.png)

Sinh tổ hợp ở menu 2:

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC18 | Cơ bản, đối chiếu trace tay | n = 5, k = 3 | C(5, 3) = 10 tổ hợp theo thứ tự từ điển | `Da sinh: 10`, `Tong so to hop theo cong thuc: 10` | PASS |
| TC19 | Biên k = 0 | n = 4, k = 0 | 1 tổ hợp rỗng | `{}`. `Da sinh: 1`, `Tong so to hop theo cong thuc: 1` | PASS |
| TC20 | Biên k = n | n = 4, k = 4 | 1 tổ hợp gồm tất cả phần tử | `{1, 2, 3, 4}`. `Da sinh: 1`, `Tong so to hop theo cong thuc: 1` | PASS |
| TC21 | Kích thước lớn nhất cho phép | n = 20, k = 10 | C(20, 10) = 184 756 tổ hợp | `Da sinh: 184756`, `Tong so to hop theo cong thuc: 184756` | PASS |
| TC22 | k lớn hơn n | n = 3, k = 5 | Báo lỗi và quay lại menu | `Loi: can 0 <= k <= n <= 20` | PASS |
| TC23 | Vượt giới hạn | n = 21, k = 3 | Báo lỗi và quay lại menu | `Loi: can 0 <= k <= n <= 20` | PASS |

![TC22: nhập k lớn hơn n](img/week_3_comb_invalid.png)

Menu chính:

| Mã | Trường hợp | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC24 | Nhập chữ thay vì số | `abc` | Thoát chương trình, không treo | Chương trình kết thúc, không sinh cấu hình | PASS |

### 5.2. Kiểm thử giới hạn số cấu hình được in

Ở mỗi test, nhóm kiểm tra số cấu hình đã sinh, dấu `...` khi còn cấu hình chưa sinh và tổng theo công thức. Nếu `limit` nhỏ hơn tổng, chương trình phải dừng sớm.

| Mã | Menu | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC25 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 2 | In 2 hoán vị đầu, có `...`, tổng 3! = 6 | `{1, 2, 3}`. Dòng cuối `{1, 3, 2}`. `Da sinh: 2`, `Tong so hoan vi theo cong thuc: 6` | PASS |
| TC26 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 0 | In đủ 6 hoán vị như bảng trace tay, không có `...` | `Da sinh: 6`, `Tong so hoan vi theo cong thuc: 6` | PASS |
| TC27 | 1. Hoán vị | n = 2, {1, 2}, `limit` = 2 | `limit` bằng tổng: in đủ 2 hoán vị, không có `...` | `{1, 2}`. Dòng cuối `{2, 1}`. `Da sinh: 2`, `Tong so hoan vi theo cong thuc: 2` | PASS |
| TC28 | 1. Hoán vị | n = 3, {3, 1, 2}, `limit` = 100 | `limit` lớn hơn tổng: in đủ 6 hoán vị, không có `...` | `Da sinh: 6`, `Tong so hoan vi theo cong thuc: 6` | PASS |
| TC29 | 1. Hoán vị | n = 10, {1, ..., 10}, `limit` = 3 | Sinh 3 hoán vị đầu rồi dừng, tổng theo công thức là 10! | `Da sinh: 3`, `Tong so hoan vi theo cong thuc: 3628800` | PASS |
| TC30 | 2. Tổ hợp | n = 5, k = 2, `limit` = 3 | In 3 tổ hợp đầu, có `...`, tổng C(5, 2) = 10 | `{1, 2}`. Dòng cuối `{1, 4}`. `Da sinh: 3`, `Tong so to hop theo cong thuc: 10` | PASS |
| TC31 | 2. Tổ hợp | n = 5, k = 0, `limit` = 4 | 1 tổ hợp rỗng, không có `...` | `{}`. `Da sinh: 1`, `Tong so to hop theo cong thuc: 1` | PASS |
| TC32 | 2. Tổ hợp | n = 20, k = 10, `limit` = 3 | Sinh 3 tổ hợp đầu rồi dừng, tổng theo công thức là C(20, 10) | `Da sinh: 3`, `Tong so to hop theo cong thuc: 184756` | PASS |
| TC33 | 3. Gray Code | n = 0, `limit` = 5 | 1 mã rỗng ứng với tập con rỗng, không có `...`, kiểm tra đúng | `{ } -> {}`. `Da sinh: 1`, `Tong so ma Gray theo cong thuc: 1`, `Kiem tra cac ma Gray da sinh: DUNG` | PASS |
| TC34 | 3. Gray Code | n = 30, `limit` = 1 | Sinh 1 mã rồi dừng, tổng theo công thức là 2³⁰, chỉ kiểm tra mã đã sinh | `Da sinh: 1`, `Tong so ma Gray theo cong thuc: 1073741824`, `Kiem tra cac ma Gray da sinh: DUNG` | PASS |
| TC35 | 3. Gray Code | n = 3, `limit` = -1 | Báo lỗi và quay lại menu | `Loi: so cau hinh can in phai >= 0` | PASS |
| TC36 | 3. Gray Code | n = 3, `limit` = `abc` | Báo lỗi, quay lại menu và dùng tiếp được | Báo lỗi, quay lại menu và chạy tiếp Gray Code n = 0 được 1 mã. `{ } -> {}`. `Da sinh: 1`, `Tong so ma Gray theo cong thuc: 1`, `Kiem tra cac ma Gray da sinh: DUNG` | PASS |

Ở bản cũ, TC34 kiểm tra Gray Code với n = 30: chương trình chỉ in 1 cấu hình nhưng vẫn sinh và kiểm tra đủ 2³⁰ mã. Bản hiện tại dừng sau cấu hình đầu, được kiểm thử riêng ở mục 5.7.

![TC34: Gray Code n = 30, chỉ in 1 mã nhưng vẫn đếm và kiểm tra đủ 2³⁰ mã](img/week_4_tc34_gray_n30.png)

TC36 lúc đầu không đạt: chương trình báo lỗi đúng nhưng sau đó thoát luôn, không quay lại menu. Nguyên nhân và cách sửa được trình bày ở mục 8.1.

![TC36: nhập chữ ở lời nhắc số cấu hình, chương trình báo lỗi rồi quay lại menu](img/week_4_tc36_invalid_limit.png)

### 5.3. Kiểm chứng số lượng và trường hợp trùng giá trị

Theo yêu cầu đề bài, các trường hợp số lượng dưới đây được chạy với `limit = 0` để đếm toàn bộ cấu hình và đối chiếu với công thức. TC42 kiểm tra thêm đầu vào trùng giá trị.

| Mã | Thuật toán | Đầu vào | Kết quả kỳ vọng | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|---|
| TC37 | Hoán vị | n = 10, mảng {1, 2, ..., 10} | 10! = 3 628 800 | `Da sinh: 3628800`, `Tong so hoan vi theo cong thuc: 3628800` | PASS |
| TC38 | Tổ hợp | n = 10, k = 5 | C(10, 5) = 252 | `Da sinh: 252`, `Tong so to hop theo cong thuc: 252` | PASS |
| TC39 | Tổ hợp | n = 20, k = 10 | C(20, 10) = 184 756 | `Da sinh: 184756`, `Tong so to hop theo cong thuc: 184756` | PASS |
| TC40 | Tổ hợp, biên k = 0 | n = 10, k = 0 | C(10, 0) = 1, chỉ có tập rỗng | `{}`. `Da sinh: 1`, `Tong so to hop theo cong thuc: 1` | PASS |
| TC41 | Gray Code | n = 10 | 2^10 = 1 024 | `Da sinh: 1024`, `Tong so ma Gray theo cong thuc: 1024`, `Kiem tra cac ma Gray da sinh: DUNG` | PASS |
| TC42 | Hoán vị, toàn phần tử trùng | n = 4, mảng {2, 2, 2, 2} | 1 hoán vị duy nhất | `{2, 2, 2, 2}`. `Da sinh: 1`, `Tong so hoan vi theo cong thuc: 1` | PASS |

TC42 kiểm tra đầu vào có tất cả phần tử trùng nhau. Với đầu vào này, Algorithm L không tìm được pivot nên dừng ngay và chỉ sinh một cấu hình.

### 5.4. Kiểm thử hiển thị tập con

Sau khi sửa phần in tập con, chương trình đã được biên dịch và chạy thử với n = 3 và n = 0. Với n = 3, chương trình in đủ 8 cặp chuỗi bit và tập con như mục 3.3. Với n = 0, kết quả là `{ } -> {}`, tổng số mã bằng 1. Cả hai trường hợp đều có `Kiem tra cac ma Gray da sinh: DUNG` ở bản hiện tại.

### 5.5. Kiểm thử lại trên bản hiện tại

TC10 đến TC42 đã được chạy lại, kết quả lưu trong [`results/report_case_regression.csv`](results/report_case_regression.csv). Cả 33 trường hợp đều đạt trên bản kiểm tra giới hạn in hết theo tổng số cấu hình.

TC15 và TC37 sinh hết 10! hoán vị, còn TC21 và TC39 sinh hết C(20, 10) tổ hợp để kiểm tra số thực tế. Các trường hợp có `limit` kiểm tra số đã sinh và tổng theo công thức riêng. TC36 kiểm tra báo lỗi rồi dùng tiếp menu. Năm trường hợp nhập chữ ở n, k và phần tử hoán vị được kiểm tra trong bộ CLI ở mục 5.7.

### 5.6. Kiểm chứng đầy đủ từ n = 0 đến 10

Phép kiểm chứng gọi các hàm sinh để duyệt hết dãy, không lấy công thức làm số đã sinh. Số tổ hợp kỳ vọng được tính riêng bằng bảng Pascal. Với Gray Code, kết quả được kiểm tra thêm mã trùng và tính chất một bit bằng `verifyGray()`.

Cả 88 bộ đều đạt, gồm hoán vị, Gray Code và tổ hợp với mọi k từ 0 đến n. Bảng dưới ghi số thực tế đã đếm từ n = 1 đến 10. Trường hợp n = 0 cũng đạt với một hoán vị rỗng, một tổ hợp rỗng và một mã Gray rỗng.

| n | Hoán vị, khớp n! | Gray Code, khớp 2ⁿ | Tổ hợp, khớp C(n,k) với k từ 0 đến n | Kết quả |
|---|---|---|---|---|
| 1 | 1 | 2 | 1, 1 | PASS |
| 2 | 2 | 4 | 1, 2, 1 | PASS |
| 3 | 6 | 8 | 1, 3, 3, 1 | PASS |
| 4 | 24 | 16 | 1, 4, 6, 4, 1 | PASS |
| 5 | 120 | 32 | 1, 5, 10, 10, 5, 1 | PASS |
| 6 | 720 | 64 | 1, 6, 15, 20, 15, 6, 1 | PASS |
| 7 | 5040 | 128 | 1, 7, 21, 35, 35, 21, 7, 1 | PASS |
| 8 | 40320 | 256 | 1, 8, 28, 56, 70, 56, 28, 8, 1 | PASS |
| 9 | 362880 | 512 | 1, 9, 36, 84, 126, 126, 84, 36, 9, 1 | PASS |
| 10 | 3628800 | 1024 | 1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1 | PASS |

Chi tiết từng bộ nằm trong [`results/count_verification.csv`](results/count_verification.csv).

### 5.7. Kiểm thử CLI dừng sớm

Sau khi đổi cách dừng, chương trình được biên dịch bằng g++ 16.2.0 với `-Wall -Wextra -Wpedantic`, không có cảnh báo. Khi kiểm thử, đầu ra được đối chiếu với hoán vị và tổ hợp từ thư viện chuẩn Python, cùng dãy Gray tính theo công thức.

Cả 60 bộ đều đạt. Các bộ kiểm tra `limit` bằng 0, bằng 1, bằng tổng và lớn hơn tổng, đầu vào rỗng, phần tử trùng, lỗi nhập liệu và tính chất một bit. Hoán vị n = 11 và n = 20 với các phần tử khác nhau bị từ chối khi `limit = 0`. Nếu mọi phần tử giống nhau, cả hai kích thước đều in đủ một hoán vị. Trường hợp n = 20 có 19 phần tử giống nhau và một phần tử khác cũng in đủ 20 hoán vị.

Gray Code n = 22, 26 và 30 với `limit = 0` bị từ chối trước khi sinh hoặc cấp phát mảng kiểm tra toàn bộ. Sau lỗi, người dùng vẫn chạy tiếp menu được. Hoán vị n = 10 vẫn được phép in toàn bộ, đã kiểm tra ở TC15. Các test từ chối và dừng sớm đều trả về trong giới hạn kiểm thử 5 giây.

| Trường hợp | Số đã sinh | Tổng theo công thức | Kết quả |
|---|---|---|---|
| Hoán vị n = 20, phần tử khác nhau, limit = 2 | 2 | 2432902008176640000 | PASS |
| Tổ hợp n = 20, k = 10, limit = 3 | 3 | 184756 | PASS |
| Gray Code n = 30, limit = 1 | 1 | 1073741824 | PASS |
| Hoán vị n = 11, phần tử khác nhau, limit = 0 | 0, bị từ chối | 39916800 | PASS |
| Hoán vị n = 11, mọi phần tử giống nhau, limit = 0 | 1 | 1 | PASS |
| Hoán vị n = 20, phần tử khác nhau, limit = 0 | 0, bị từ chối | 2432902008176640000 | PASS |
| Hoán vị n = 20, mọi phần tử giống nhau, limit = 0 | 1 | 1 | PASS |
| Hoán vị n = 20, có 19 phần tử giống nhau, limit = 0 | 20 | 20 | PASS |
| Gray Code n = 26, limit = 0 | 0, bị từ chối | 67108864 | PASS |
| Gray Code n = 30, limit = 0 | 0, bị từ chối | 1073741824 | PASS |

Với Gray Code chỉ sinh một phần, kết quả kiểm tra chỉ áp dụng cho các mã đã sinh. Kiểm chứng đầy đủ được chạy riêng ở mục 5.6 và không dựa vào dòng tổng theo công thức của CLI.

## 6. Đánh giá thực nghiệm

### 6.1. Phương pháp đo và bộ dữ liệu

Phần benchmark nằm trong `benchmark.h`, được đưa vào `comb_gen.cpp` bằng `#include` và chạy từ menu 4. Các hàm chính gồm:

| Hàm | Dòng | Chức năng |
|---|---|---|
| `fact`, `binom` | 13 đến 23 | Tính số cấu hình theo công thức n! và C(n, k) |
| `generate` | 26 đến 45 | Sinh toàn bộ cấu hình nhưng không in, trả về số cấu hình đếm được |
| `measure` | 48 đến 58 | Chạy 1 lần khởi động và 5 lần đo, trả về median |
| `runAlgo` | 61 đến 89 | Đo một thuật toán với n chạy trong một khoảng, in và ghi từng dòng kết quả |
| `runBenchmark` | 91 đến 105 | Gọi `runAlgo` cho 3 thuật toán và ghi file `bench_results.csv` |

Mã nguồn: [`benchmark.h`](benchmark.h).

Benchmark gọi trực tiếp `nextPermutation` và `nextCombination` trong `comb_gen.cpp`, nên đo đúng code đã nộp. Gray Code dùng đúng công thức `i ^ (i >> 1)` như menu 3.

Thời gian đo không bao gồm phần in. Với Gray Code, benchmark cũng không tính `verifyGray()`, vì việc kiểm tra đúng sai đã được thực hiện ở menu 3. Biến `grayXor` giữ lại kết quả các mã Gray, nếu không có biến này thì trình biên dịch sẽ bỏ luôn vòng lặp khi tối ưu `-O2`.

Mỗi lần chạy, chương trình đếm số cấu hình sinh ra và so với n!, C(n, k), 2ⁿ. Nếu không khớp thì chương trình in `SAI SO LUONG`. Tất cả các dòng đều khớp.

Mỗi bộ dữ liệu chạy 1 lần khởi động và không ghi nhận thời gian lần này. Sau đó, chương trình chạy thêm 5 lần, sắp xếp các thời gian đo và lấy giá trị ở giữa làm trung vị.

#### Bộ dữ liệu thử

| Thuật toán | Đầu vào | Lý do chọn |
|---|---|---|
| Hoán vị | n = 8 đến 12, mảng {1, ..., n} | 12! ≈ 4,8 × 10⁸ chạy trong khoảng 1,4 giây, 13! lâu hơn khoảng 13 lần |
| Tổ hợp | n từ 16 đến 30, mỗi lần tăng 2, k = n/2 | k = n/2 cho C(n, k) lớn nhất ứng với mỗi n, và n chẵn để k đúng bằng một nửa n |
| Gray Code | n từ 16 đến 28, mỗi lần tăng 2 | 2²⁸ ≈ 2,7 × 10⁸ mã, mỗi lần n tăng 2 thì số mã gấp 4 nên dễ đối chiếu |

### 6.2. Môi trường và kết quả

Nhóm đo cả ba thuật toán trên máy 1 bằng cùng một bản benchmark.

| Thành phần | Máy 1 |
|---|---|
| CPU | Intel Core i7-11800H thế hệ 11, 8 nhân / 16 luồng, 2.30 GHz |
| RAM | 8 GB |
| Trình biên dịch | g++ 12.1.0, MinGW-W64 x86_64, posix-seh |
| Cờ biên dịch | `g++ -std=c++17 -O2 comb_gen.cpp -o comb_gen` |
| Bản benchmark | `benchmark.h` tại commit [`1a2a6f6`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/1a2a6f6/benchmark.h) |

Phép đo dùng bộ dữ liệu và cách lấy trung vị ở mục 6.1. Benchmark không in cấu hình nên giới hạn in không ảnh hưởng tới kết quả.

Ở lần chạy đầu, số liệu Gray Code dao động từ 0,48 đến 0,62 ns mỗi mã. Ứng dụng nền và chế độ nguồn có thể ảnh hưởng đến kết quả. Nhóm chạy lại 3 lần, cả ba lần đều ra 0,46 đến 0,50 ns. Các bảng dưới đây lấy số liệu của lần đầu tiên trong 3 lần này.

Bảng 1. Sinh hoán vị bằng Algorithm L trên máy 1

| n | Số cấu hình n! | Thời gian trung vị, ms | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 8 | 40 320 | 0,1249 | 3,10 |  |  |
| 9 | 362 880 | 1,093 | 3,01 | 8,75 | 9 |
| 10 | 3 628 800 | 10,22 | 2,82 | 9,35 | 10 |
| 11 | 39 916 800 | 113,1 | 2,83 | 11,07 | 11 |
| 12 | 479 001 600 | 1 375 | 2,87 | 12,16 | 12 |

Bảng 2. Sinh tổ hợp với k = n/2 trên máy 1

| n | k | Số cấu hình C(n, k) | Thời gian trung vị, ms | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|---|
| 16 | 8 | 12 870 | 0,0332 | 2,58 |  |  |
| 18 | 9 | 48 620 | 0,125 | 2,57 | 3,77 | 3,78 |
| 20 | 10 | 184 756 | 0,476 | 2,58 | 3,81 | 3,80 |
| 22 | 11 | 705 432 | 1,821 | 2,58 | 3,83 | 3,82 |
| 24 | 12 | 2 704 156 | 7,292 | 2,70 | 4,00 | 3,83 |
| 26 | 13 | 10 400 600 | 28,37 | 2,73 | 3,89 | 3,85 |
| 28 | 14 | 40 116 600 | 104,7 | 2,61 | 3,69 | 3,86 |
| 30 | 15 | 155 117 520 | 414,1 | 2,67 | 3,95 | 3,87 |

Bảng 3. Sinh mã Gray trên máy 1, không tính phần kiểm tra

| n | Số cấu hình 2ⁿ | Thời gian trung vị, ms | ns/cấu hình | Tỉ lệ thời gian | Tỉ lệ công thức |
|---|---|---|---|---|---|
| 16 | 65 536 | 0,0309 | 0,47 |  |  |
| 18 | 262 144 | 0,1207 | 0,46 | 3,91 | 4 |
| 20 | 1 048 576 | 0,4852 | 0,46 | 4,02 | 4 |
| 22 | 4 194 304 | 1,934 | 0,46 | 3,99 | 4 |
| 24 | 16 777 216 | 7,75 | 0,46 | 4,01 | 4 |
| 26 | 67 108 864 | 32,49 | 0,48 | 4,19 | 4 |
| 28 | 268 435 456 | 128 | 0,48 | 3,94 | 4 |

Toàn bộ kết quả được lưu trong file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv). Ở bản hiện tại, file này và `bench_ns_per_item.csv` đã được chuyển vào thư mục [`results/`](results/).

Nhận xét:

1. Thời gian sinh mỗi cấu hình khá ổn định. Hoán vị khoảng 2,8 đến 3,1 ns mỗi cấu hình, tổ hợp 2,6 đến 2,7 ns, Gray Code 0,46 đến 0,48 ns.
2. Tỉ lệ thời gian gần với tỉ lệ số cấu hình. Ví dụ, khi n tăng từ 11 lên 12, số hoán vị tăng 12 lần và thời gian tăng 12,16 lần.
3. Trong benchmark, mỗi mã Gray mất khoảng 0,47 ns, nhanh hơn khoảng 6 lần so với mỗi hoán vị hoặc tổ hợp. Hai thuật toán này mất khoảng 2,6 đến 3,1 ns mỗi cấu hình. Benchmark Gray Code không gọi `verifyGray()` nên con số này không phản ánh trực tiếp tốc độ của menu 3.

### 6.3. Biểu đồ và nhận xét

Các biểu đồ được vẽ bằng Google Sheets từ file [`bench_results.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_results.csv) ở mục 6.2:

- Biểu đồ 1, 2, 3 thể hiện tổng thời gian sinh theo n qua cột `median_ms`. Mỗi thuật toán có một hình. Trục dọc dùng thang log vì thời gian tăng rất nhanh. Với hoán vị, thời gian tăng từ 0,12 ms lên 1 375 ms khi n tăng từ 8 lên 12.
- Biểu đồ 4 so sánh thời gian sinh một cấu hình của cả ba thuật toán qua cột `ns_per_item`. Dữ liệu lấy từ [`bench_ns_per_item.csv`](https://github.com/QuangquyNguyenvo/DSA_final_project/blob/07548d7/bench_ns_per_item.csv). File này chỉ xếp lại cột `ns_per_item` để dễ vẽ.

Biểu đồ 1, 2, 3. Thời gian sinh theo n của hoán vị, tổ hợp với k = n/2 và Gray Code

![Bảng bench_results.csv và biểu đồ thời gian sinh theo n của ba thuật toán](img/week_4_chart_time_sheet.png)

Biểu đồ 4. Thời gian sinh một cấu hình theo n

![Bảng ns_per_item và biểu đồ thời gian sinh một cấu hình của ba thuật toán theo n](img/week_4_chart_ns_sheet.png)

Nhận xét:

1. Thời gian chạy tăng gần với số cấu hình. Trên thang log, đường Gray Code và tổ hợp gần như thẳng. Gray Code tăng theo 2ⁿ, tổ hợp với k = n/2 tăng chậm hơn 2ⁿ một chút. Riêng đường hoán vị hơi cong lên, vì mỗi lần n tăng 1 thì số hoán vị nhân thêm n + 1, hệ số này lớn dần.
2. Đường biểu diễn ở biểu đồ 4 gần như nằm ngang. Thời gian sinh một cấu hình ít thay đổi khi n tăng, phù hợp với phần phân tích ở mục 4.
3. Tổng thời gian của tổ hợp và Gray Code khá gần nhau trong bộ dữ liệu này. Gray Code có nhiều cấu hình hơn khoảng 5 đến 7 lần nhưng sinh mỗi cấu hình nhanh hơn khoảng 5,5 lần.

### 6.4. Đo riêng chi phí in kết quả

Chương trình dùng `ios::sync_with_stdio(false)` để tắt đồng bộ giữa nhập xuất C++ và C. Nhóm đo riêng thời gian in trước và sau khi thêm thiết lập này.

Nhóm cho cả hai bản in hết 10! hoán vị và 2²² mã Gray ra file, tổng cộng khoảng 7,8 triệu dòng. Mỗi bản chạy 2 lần trên máy 2, dùng g++ 16.2.0 với cờ `-O2 -static`.

| Bản | Lần 1 | Lần 2 |
|---|---|---|
| Trước khi sửa, commit `5d553d1` | 11,98 s | 11,54 s |
| Sau khi sửa, commit `997cfa2` | 5,71 s | 5,90 s |

Thời gian in giảm còn khoảng một nửa. Nhóm dùng lệnh `cmp` để so sánh và kết quả của hai bản giống hệt nhau. Mỗi bản chỉ chạy 2 lần nên số liệu này dùng để minh họa, chưa đủ để kết luận cho mọi máy. Benchmark ở mục 6.1 đến 6.2 không in nên không bị ảnh hưởng.

Commit đối chiếu phép đo: https://github.com/QuangquyNguyenvo/DSA_final_project/commit/997cfa2

Phép so sánh output trước/sau ở trên thuộc thời điểm tối ưu nhập xuất, trước khi bổ sung cách in subset. Các ảnh minh chứng cũ có thể chỉ hiển thị chuỗi bit. Cách hiển thị hiện tại được minh họa tại mục 3.3.

### 6.5. Đo tổ hợp khi k thay đổi

Bộ đo ban đầu dùng k = n/2. Phép đo bổ sung giữ n = 26 và thay đổi k để xem chi phí khi k gần n. Số liệu dưới đây được đo trên máy 2 với Intel Core i7-11800H, RAM 16 GB, Windows 11 Pro và g++ 16.2.0. Cờ biên dịch gồm `-O2 -static`. Đây là môi trường khác máy 1 dùng g++ 12.1.0, nên các số liệu được trình bày riêng.

Với k gần n, mỗi lượt chỉ có vài chục hoặc vài trăm tổ hợp. Để thời gian đo không quá ngắn, mỗi lô lặp lại việc sinh hết dãy cho tới khoảng hai triệu cấu hình trở lên. Chương trình chạy một lô khởi động, đo thêm năm lô rồi lấy trung vị. Phép đo không in cấu hình, nhưng có tính khởi tạo vector, kiểm tra dừng và kiểm tra số lượng mỗi lượt.

| k | C(26,k) mỗi lượt | Số lượt trong một lô | Thời gian một lô, ms | ns/cấu hình | Số vị trí phải lùi trung bình |
|---|---|---|---|---|---|
| 2 | 325 | 6153 | 5,5975 | 2,80 | 0,080 |
| 13 | 10400600 | 1 | 36,6176 | 3,52 | 0,929 |
| 24 | 325 | 6153 | 15,0025 | 7,50 | 8,000 |
| 25 | 26 | 76923 | 21,8176 | 10,91 | 12,500 |

Khi k = 24 và k = 25, mỗi cấu hình tốn nhiều thời gian hơn so với k = 2 và k = 13. Kết quả phù hợp với số vị trí phải lùi trung bình k/(n-k+1), lần lượt là 8 và 12,5 khi k = 24 và k = 25. Thời gian không tỉ lệ đúng hoàn toàn với số vị trí vì phép đo còn có chi phí khởi tạo và điều khiển vòng lặp.

Dữ liệu nằm trong [`results/bench_combination_k.csv`](results/bench_combination_k.csv). Các số liệu này được trình bày riêng với kết quả trên máy 1 vì khác môi trường đo.

## 7. Self-Explanation theo từng yêu cầu đề bài

Bảng dưới giải thích cách làm và lý do chọn cách làm cho từng yêu cầu. Các ví dụ và kết quả kiểm tra nằm ở những mục được dẫn trong cột cuối.

| Yêu cầu đề bài | Tự giải thích | Chi tiết |
|---|---|---|
| Algorithm L | Chọn pivot phải nhất và phần tử thay thế nhỏ nhất có thể để dãy tăng ít nhất. Đảo đuôi về tăng dần giúp tạo đúng hoán vị kế tiếp mà không bỏ qua cấu hình nào. | Mục 3.1 |
| Tổ hợp theo thứ tự từ điển | Dãy tăng giúp mỗi cách chọn chỉ được biểu diễn một lần. Tăng vị trí phải nhất còn tăng được rồi đặt lại đuôi nhỏ nhất giúp giữ đúng thứ tự và còn đủ chỗ cho các phần tử sau. | Mục 3.2 |
| Sinh tập con bằng Gray Code | Mỗi bit cho biết một phần tử có được chọn hay không. Công thức `i ^ (i >> 1)` tính trực tiếp từng mã, còn việc in thêm tập con giúp dễ nhìn ra các phần tử được chọn. | Mục 3.3 |
| Số lượng khớp công thức với n ≥ 10 | Đếm toàn bộ cấu hình đã sinh để so với n!, C(n, k) và 2ⁿ, thay vì chỉ kiểm tra vài dòng đầu. Đầu vào dùng để đối chiếu n! có các phần tử khác nhau, còn Gray Code được kiểm tra thêm mã trùng. | Mục 5.3, 5.6, 6.2 |
| Hai tập con liên tiếp khác đúng một phần tử | Công thức Gray bảo đảm XOR hai mã liên tiếp chỉ còn một bit 1, tương ứng với thêm hoặc bỏ một phần tử. Hàm `verifyGray()` dùng popcount để kiểm tra lại trên mã vừa sinh. | Mục 3.3 |
| Phân tích chi phí mỗi cấu hình và tổng thời gian | Nhóm tách phần sinh khỏi phần in vì in một cấu hình còn phải duyệt các phần tử của nó. Benchmark bỏ phần in và kiểm tra Gray Code để đo riêng thời gian sinh. | Mục 4, 6 |
| Test nhỏ, lớn và trường hợp biên | Trace tay kiểm tra từng bước, còn dữ liệu lớn kiểm tra số lượng và thời gian chạy. Đầu vào rỗng, trùng giá trị và nhập sai giúp phát hiện lỗi dễ bị bỏ sót khi chỉ thử dữ liệu thông thường. | Mục 3, 5 |
| CLI in một số cấu hình đầu | Chương trình dừng ngay khi đủ `limit` để không phải sinh toàn bộ dãy. Số đã sinh và tổng theo công thức được in riêng để tránh nhầm kết quả tính toán với kết quả kiểm chứng toàn bộ. | Mục 2.3, 5.7 |

Sản phẩm gồm mã nguồn C++17, CLI, benchmark xuất CSV, bảng kiểm thử, biểu đồ và báo cáo giải thích ba thuật toán.

## 8. Khó khăn, phân công và quá trình thực hiện

### 8.1. Khó khăn và hướng giải quyết

- Lúc đầu, nhóm tìm hiểu và kiểm chứng chưa đủ kỹ nên phải quay lại phân tích đề bài và trace tay. Nhờ đó, nhóm làm rõ cách chọn pivot, giới hạn của từng vị trí và cách đặt lại đoạn đuôi.
- Bản benchmark Gray Code đầu tiên gọi `verifyGray()` nhưng không dùng kết quả trả về. Cách đo này có thể bị trình biên dịch tối ưu hoặc tính cả thời gian kiểm tra. Nhóm bỏ phần kiểm tra khỏi benchmark, XOR dồn các mã vào `grayXor` và đo lại.
- Số liệu từ hai máy khó so sánh nên nhóm đo lại cả ba thuật toán trên máy 1 bằng cùng một bản benchmark.
- Khi số cấu hình lớn, in hết kết quả mất nhiều thời gian. Nhóm thêm `limit` cho cả ba menu và dùng `ios::sync_with_stdio(false)` để tăng tốc in. Bản đầu vẫn sinh hết dãy, còn bản hiện tại dừng khi đủ `limit`. Kiểm chứng toàn bộ được chạy riêng để không nhầm tổng theo công thức với số đã đếm.
- Khi nhập chữ ở `readLimit()`, chương trình từng báo lỗi rồi thoát. Nhóm dùng `cin.clear()` và `cin.ignore(1000, '\n')` để xóa lỗi và bỏ phần nhập sai. Ở bản cuối, các ô nhập n, k và phần tử cũng xử lý theo cách này qua `readNumber()`.
- Chuỗi bit chưa cho thấy rõ các phần tử được chọn nên nhóm in thêm tập con bên cạnh mã Gray.
- Thời gian benchmark có dao động giữa các lần chạy. Nhóm lấy trung vị của năm lần đo sau một lần khởi động và chạy lại khi số liệu thay đổi nhiều.

Chương trình hiện còn giới hạn kích thước đầu vào. Phần kiểm tra Gray Code cần bộ nhớ tăng theo 2ⁿ. Thời gian chạy cũng phụ thuộc vào máy và điều kiện đo.

### 8.2. Phân công công việc

| Thành viên | MSSV | Công việc chính |
|---|---|---|
| Đào Nghiệm Minh | 25110042 | Viết chú thích mã nguồn, chụp ảnh kiểm thử và hoàn thiện báo cáo tuần 1.<br>Tìm hiểu và cài đặt Gray Code bản đầu, hỗ trợ kiểm thử và tích hợp chương trình.<br>Hoàn thiện CLI với màu chữ, khung viền và lời nhắc nhập dữ liệu.<br>Phân tích độ phức tạp của ba thuật toán, xây dựng benchmark bản đầu và đo hoán vị, tổ hợp.<br>Thêm `readLimit()`, giới hạn in cho cả ba menu và tô đỏ thông báo lỗi.<br>Đo lại cả ba thuật toán trên máy 1, cập nhật CSV và vẽ bốn biểu đồ bằng Google Sheets.<br>Thêm phần in tập con, kiểm thử với n = 3 và n = 0.<br>Phụ trách bộ kiểm chứng số lượng với n từ 0 đến 10 và mọi k hợp lệ.<br>Phụ trách benchmark thay đổi k trên máy 2, lưu CSV và thông tin môi trường đo.<br>Viết các phần tổng quan, CLI, độ phức tạp, benchmark và hướng dẫn chạy. Tổng hợp báo cáo dự án, cập nhật ảnh benchmark và minh chứng. |
| Nguyễn Võ Quang Quý | 25110055 | Khởi tạo GitHub repository, cài đặt Algorithm L và thuật toán sinh tổ hợp bằng C++, dựng khung báo cáo.<br>Review Gray Code, nghiên cứu cách sinh bằng XOR, phân tích thiết kế và cải tiến mã nguồn.<br>Xây dựng hàm kiểm chứng Gray Code.<br>Phát hiện lỗi phép đo Gray Code, viết lại `benchmark.h` và đo lại Gray Code.<br>Trace tay và kiểm thử hoán vị, tổ hợp.<br>Phát hiện và sửa lỗi nhập chữ ở `readLimit()`, bổ sung xử lý nhập chữ ở các ô nhập số.<br>Dọn mã nguồn, tăng tốc in và đo thời gian in trước và sau khi sửa.<br>Kiểm thử giới hạn in, chạy lại các test cũ và kiểm tra bản cuối.<br>Phụ trách CLI dừng sớm và giới hạn in hết theo tổng số cấu hình.<br>Phụ trách bộ test CLI và chạy lại TC10 đến TC42, lưu kết quả vào CSV.<br>Viết các phần kiểm thử, tích hợp mã nguồn, khó khăn, kế hoạch tuần 4, đối chiếu yêu cầu và tài liệu tham khảo. Tham gia tổng hợp báo cáo. |
| Cả nhóm | | Phân tích đề bài và lập kế hoạch.<br>Kiểm tra chéo mã nguồn và nội dung báo cáo.<br>Hoàn thiện sản phẩm, chuẩn bị vấn đáp và nộp bài. |

Phân công chi tiết theo từng giai đoạn được trình bày trong báo cáo [tuần 1](reports/week1.md), [tuần 2](reports/week2.md), [tuần 3](reports/week3.md) và [tuần 4](reports/week4.md).

### 8.3. Quá trình thực hiện

Nhóm sử dụng Git và GitHub để chia nhánh công việc, review qua pull request và theo dõi lịch sử thay đổi. Danh sách commit, pull request và minh chứng từng giai đoạn được lưu trong các báo cáo tại thư mục [`reports/`](reports/).

Nhóm bắt đầu từ phân tích đề bài, lập kế hoạch và cài đặt hoán vị, tổ hợp. Sau đó bổ sung Gray Code và kiểm chứng. Các giai đoạn tiếp theo gồm tích hợp CLI, phân tích độ phức tạp, xây dựng benchmark, đo lại trong cùng môi trường, vẽ biểu đồ và hoàn thiện chương trình. Sau cùng, nhóm thêm cách in tập con bên cạnh chuỗi bit để người dùng dễ theo dõi kết quả.

![Kế hoạch thực hiện dự án](img/Planning.png)

## 9. Nguồn kiến thức, AI Usage Log và tài liệu tham khảo

### 9.1. Nguồn gốc kiến thức

Dự án sử dụng kiến thức về tổ hợp, thứ tự từ điển, biểu diễn nhị phân, Boolean Algebra, Karnaugh Map và các phép toán bitwise. Các thuật toán được giải thích qua nguyên lý hoạt động, bảng trace tay và kết quả kiểm thử. Phần hiệu năng được đối chiếu với phân tích độ phức tạp.

Báo cáo tổng hợp nội dung, số liệu và minh chứng từ các báo cáo tuần, đồng thời cập nhật phần hiển thị tập con bên cạnh mã Gray. Các tài liệu tham khảo về thuật toán, phép toán bit, đo thời gian và nhập xuất C++ được liệt kê tại mục 9.3.

### 9.2. AI Usage Log

Phần dưới tóm tắt nội dung khai báo trong bốn báo cáo tuần.

| Giai đoạn | Nội dung khai báo |
|---|---|
| [Tuần 1](reports/week1.md#7-khai-báo-sử-dụng-ai) | Nhóm ghi nhận gần như không sử dụng LLM, chủ yếu dùng Google để tìm kiếm và tra cứu tài liệu. |
| [Tuần 2](reports/week2.md#81-khai-báo-sử-dụng-ai-và-nguồn-gốc-kiến-thức) | Nhóm không sử dụng AI trong nghiên cứu, viết mã nguồn và viết báo cáo. Các tài liệu được tìm kiếm qua Google. |
| [Tuần 3](reports/week3.md#81-khai-báo-sử-dụng-ai-và-nguồn-gốc-kiến-thức) | Sau khi hoàn thành cài đặt, kiểm thử và benchmark, nhóm dùng Gemini 3.8 Flash để rà soát `#pragma once`, `inline`, độ phức tạp của Gray Code và cách đánh giá benchmark. AI hỗ trợ giải thích và đối chiếu kiến thức, không tham gia viết mã nguồn hay thay thế việc kiểm chứng của nhóm. |
| [Tuần 4](reports/week4.md#91-khai-báo-sử-dụng-ai-và-nguồn-gốc-kiến-thức) | Nhóm không sử dụng AI. Công việc chủ yếu là sửa lỗi, tối ưu và hoàn thiện chương trình dựa trên mã nguồn đã có. Nhóm tra cứu tài liệu về xử lý nhập liệu và nhập xuất C++ khi cần. |

Minh chứng tuần 3: [Cuộc trò chuyện với Gemini](https://share.gemini.google/RBkOQo69pslz).

### 9.3. Tài liệu tham khảo

Các nguồn sau được tổng hợp từ danh sách tài liệu trong các báo cáo tiến độ. Danh sách theo từng giai đoạn và video minh chứng được giữ tại thư mục [`reports/`](reports/).

[1] VNOI Wiki: Phép toán bit

[https://wiki.vnoi.info/algo/basic/bitwise-operators](https://wiki.vnoi.info/algo/basic/bitwise-operators)

Nội dung liên quan: Các toán tử bitwise, XOR, phép dịch bit và ứng dụng trong lập trình.

[2] GeeksforGeeks: Generate n-bit Gray Codes

[https://www.geeksforgeeks.org/dsa/generate-n-bit-gray-codes/](https://www.geeksforgeeks.org/dsa/generate-n-bit-gray-codes/)

Nội dung liên quan: Các phương pháp sinh Gray Code, công thức `G(i) = i ^ (i >> 1)` và ví dụ sinh mã Gray bằng thao tác bitwise.

[3] CP-Algorithms: Gray Code

[https://cp-algorithms.com/algebra/gray-code.html](https://cp-algorithms.com/algebra/gray-code.html)

Nội dung liên quan: Binary Reflected Gray Code, công thức chuyển đổi giữa mã nhị phân và mã Gray, cùng các tính chất của dãy Gray Code.

[4] Viblo: Thao tác xử lý bit và ứng dụng

[https://viblo.asia/p/thao-tac-xu-ly-bit-va-ung-dung-bit-manipulation-3kY4gxl9JAe](https://viblo.asia/p/thao-tac-xu-ly-bit-va-ung-dung-bit-manipulation-3kY4gxl9JAe)

Nội dung liên quan: Các thao tác xử lý bit và ứng dụng trong lập trình.

[5] Stack Overflow: List of ANSI color escape sequences

[https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences](https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences)

Nội dung liên quan: Danh sách mã ANSI escape dùng để tô màu chữ trên terminal.

[6] cppreference: std::chrono::steady_clock

[https://en.cppreference.com/w/cpp/chrono/steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock)

Nội dung liên quan: Đồng hồ đo thời gian không bị ảnh hưởng khi chỉnh giờ hệ thống, dùng để đo thời gian chạy trong benchmark.

[7] VNOI Wiki: Độ phức tạp thời gian

[https://wiki.vnoi.info/algo/basic/computational-complexity](https://wiki.vnoi.info/algo/basic/computational-complexity)

Nội dung liên quan: Cách đánh giá độ phức tạp thời gian của thuật toán và ký hiệu Big-O.

[8] Viblo: Cấu trúc dữ liệu và Giải thuật Bài 3: Độ phức tạp thời gian và Ký pháp Big-O

[https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-3-do-phuc-tap-thoi-gian-time-complexity-va-ky-phap-big-o-1QLxnmjO4Aw](https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-3-do-phuc-tap-thoi-gian-time-complexity-va-ky-phap-big-o-1QLxnmjO4Aw)

Nội dung liên quan: Đánh giá thuật toán theo tốc độ tăng của số phép toán thay vì thời gian đo bằng giây, các cấp độ phức tạp thường gặp.

[9] Viblo: Cấu trúc dữ liệu và Giải thuật Bài 8: Giới thiệu về phân tích khấu hao

[https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-8-gioi-thieu-ve-amortized-analysis-phan-tich-khau-hao-pPLkNbleJRZ](https://viblo.asia/p/cau-truc-du-lieu-va-giai-thuat-bai-8-gioi-thieu-ve-amortized-analysis-phan-tich-khau-hao-pPLkNbleJRZ)

Nội dung liên quan: Phân tích khấu hao, tính chi phí trung bình của một thao tác trong một chuỗi thao tác liên tiếp.

[10] GeeksforGeeks: Measure execution time of a function in C++

[https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/](https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/)

Nội dung liên quan: Đo thời gian chạy của một hàm bằng thư viện `<chrono>`, lấy thời điểm trước và sau khi chạy rồi tính hiệu.

[11] USACO Guide: Time Complexity

[https://usaco.guide/bronze/time-comp](https://usaco.guide/bronze/time-comp)

Nội dung liên quan: Ký hiệu Big-O, độ phức tạp của các vòng lặp, độ phức tạp O(2ⁿ) khi duyệt mọi tập con và O(n!) khi duyệt mọi hoán vị.

[12] GeeksforGeeks: How to Handle Wrong Data Type Input in C++?

[https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/](https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/)

Nội dung liên quan: Xử lý khi người dùng nhập sai kiểu dữ liệu, dùng `cin.clear()` để xóa trạng thái lỗi của `cin` và `cin.ignore()` để bỏ phần nhập sai còn lại.

[13] GeeksforGeeks: Fast I/O for Competitive Programming

[https://www.geeksforgeeks.org/dsa/fast-io-for-competitive-programming/](https://www.geeksforgeeks.org/dsa/fast-io-for-competitive-programming/)

Nội dung liên quan: Tăng tốc nhập xuất bằng `ios_base::sync_with_stdio(false)`, tắt đồng bộ giữa luồng nhập xuất của C++ và C.

[14] Viblo: Các kĩ năng thi cử 10.1: Kĩ thuật tối ưu tốc độ chương trình C++

[https://viblo.asia/p/cac-ki-nang-thi-cu-101-ki-thuat-toi-uu-toc-do-chuong-trinh-c-Yym40njjL91](https://viblo.asia/p/cac-ki-nang-thi-cu-101-ki-thuat-toi-uu-toc-do-chuong-trinh-c-Yym40njjL91)

Nội dung liên quan: Giải thích vì sao tắt đồng bộ giữa `cin`, `cout` với luồng chuẩn của C giúp chương trình nhập xuất nhanh hơn.
