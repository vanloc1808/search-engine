# Chương trình tìm kiếm siêu cấp đỉnh cao

## 1. TF & IDF
|           | TF                                                                                                                                                                                                                            | IDF                                                                                                                                                                          |
|-----------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Cấu trúc  | word : **Từ** <br> count : **Số lượng**                                                                                                                                                                                       | word : **Từ** <br> value : **IDF value** <br> name : **Tên folder quản lý**                                                                                                  |
| Mục tiêu  | Tính được tỉ lệ tần suất / số lượng từ trong file                                                                                                                                                                             | Tính được độ phổ biến của từ trong các file hiện hữu trong folder                                                                                                            |
| Danh sách | size : Số lượng từ thực tế <br> capacity : Kích thước cấp phát <br> totalCount : Tổng số từ của toàn bộ danh sách <br> arrNorm : Chứa dữ liệu TF cho data **_không dấu_** <br> arrTele : Chứa dữ liệu TF cho data **_telex_** | size : Số lượng từ thực tế <br> capacity : Kích thước cấp phát <br> arrNorm : Chứa dữ liệu IDF cho data **_không dấu_** <br> arrTele : Chứa dữ liệu IDF cho data **_telex_** |

## 2. Các hàm phụ trợ

- [x] Sắp xếp mảng các string
- [x] Liệt kê file
- [ ] Chuyển đổi từ dạng tiếng việt sang LaTin đơn giản (_WIP_)
- [ ] Tối giản hóa ký tự

## 3. Quá trình thực hiện

- Build hệ thống thư mục
- Đọc file UTF-16LE :arrow_right: Mảng string Latin (_Dual type_) :arrow_right: Tối giản ký tự :arrow_right: Lưu vào **TF_List** :arrow_right: Lưu vào file
- Từ các file **TF_List** đã có :arrow_right: Build **IDF** :arrow_right: Build **IDF_List** :arrow_right: Lưu vào file
- Khi search :arrow_right: Tách từ :arrow_right: Chuẩn hóa :arrow_right: Tìm từ trong **IDF_List** :arrow_right: từ **_name_** trích xuất **TF** :arrow_right: TF*IDF :arrow_right: Lưu đường dẫn file vào danh sách
