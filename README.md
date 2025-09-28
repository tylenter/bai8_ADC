<img width="506" height="188" alt="image" src="https://github.com/user-attachments/assets/84ee9f42-7639-476b-a0bb-acd25b1dce9f" />CÁC BƯỚC THỰC HIỆN:
1. Cấu hình ADC:
   - Bật clock cho GPIOA và ADC1.
   - Cấu hình chân PA0 ở chế độ Analog input.
   - Khởi tạo ADC ở chế độ độc lập, không quét, không chạy liên tục, kích hoạt bằng phần mềm.
   - Chọn kênh ADC0 (PA0) 
   - Bật ADC, reset và hiệu chuẩn

    <img width="884" height="568" alt="image" src="https://github.com/user-attachments/assets/6198924b-3f84-4309-856d-b54510cf78c6" />

2. Cấu hình USART1:
   - Bật clock cho GPIOA và USART1.
   - Cấu hình chân PA9 làm TX (Alternate Function Push-Pull).
   - Cấu hình chân PA10 làm RX (Input Floating).
   - Khởi tạo USART1: Baudrate = 9600, 8 bit dữ liệu, 1 bit stop, không parity, không flow control.
   - Bật USART1.

<img width="1149" height="530" alt="image" src="https://github.com/user-attachments/assets/ae9b2755-e122-4243-b214-290d2eb82835" />

3. Cấu hình timer2:
   - Bật clock cho TIM2.
   - Đặt bộ chia tần số (Prescaler = 72 - 1) → Timer chạy ở 1 MHz (1 tick = 1 µs).
   - Đặt ARR = 0xFFFF (giá trị đếm tối đa).
   - Bật TIM2.

  <img width="669" height="207" alt="image" src="https://github.com/user-attachments/assets/bb4fd92c-37ea-42b4-b8f1-008cfa27cc7a" />

4. Cấu hình delay:

   <img width="506" height="188" alt="image" src="https://github.com/user-attachments/assets/36236312-b670-4e34-87ef-b0950c2968e4" />

5. Hàm main:

   <img width="921" height="586" alt="image" src="https://github.com/user-attachments/assets/4cf8af9a-0623-4b72-9d67-4fa63520daea" />

6. Kết quả:
   - Sau mỗi 500 ms, trên cửa sổ Terminal sẽ hiển thị giá trị đọc được từ chân PA0 của ADC.
   - Mỗi lần hiển thị gồm 2 thông tin:
     + ADC = … → giá trị số ADC (0 → 4095).
     + Voltage = … mV → giá trị điện áp tương ứng tại chân PA0 (0 → 3300 mV).
