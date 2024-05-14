# Những việc đã làm được:
- Kết nối wifi.
- Kết nối được mqtt.
- Hàm bật tắt led (ledSetState).
- Hàm đóng/mở cửa (doorSetState).
- Hàm bật/tắt quạt (fanSetState).
- Hàm chỉnh tốc độ quạt (fanSetLevel).
- Phản hồi các lệnh điều khiển về server (thành công?).
# Những việc cần làm:
- Chức năng hẹn giờ của LED.
- Đồng bộ trạng thái của các thiết bị khi esp bắt đầu kêt nối (start or reconnect). Sử dụng mqtt hoặc http.
+ MQTT: đã có sẵn các hàm init, publish.
+ HTTP: theo mô hình request - response. Phù hợp hơn với mục tiêu nhưng chưa có sẵn, phải viết thêm.
## Xem các file .h và .c trong thư mục components.