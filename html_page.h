const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>WebSocket LED Control</title>
</head>
<body>

  <button onclick="toggleLed('led1')">Toggle LED 1</button>
  <button onclick="toggleLed('led2')">Toggle LED 2</button>

  <script>
    const socket = new WebSocket('ws://'+window.location.hostname+':81/');

    // Sự kiện khi kết nối được mở
    socket.addEventListener('open', (event) => {
      console.log('WebSocket connection opened.');
    });

    // Sự kiện khi nhận được dữ liệu từ server
    socket.addEventListener('message', (event) => {
      console.log('Received message from server:', event.data);

      // Xử lý trạng thái của đèn từ dữ liệu nhận được
      const ledStatus = JSON.parse(event.data);
      console.log('LED 1:', ledStatus.led1);
      console.log('LED 2:', ledStatus.led2);
    });

    // Hàm gửi yêu cầu điều khiển đèn
    function toggleLed(led) {
      const action = `toggle${led.charAt(0).toUpperCase()}${led.slice(1)}`;
      const request = { action: action };

      // Chuyển đối tượng thành chuỗi JSON
      const jsonString = JSON.stringify(request);

      // Gửi chuỗi JSON tới server qua WebSocket
      socket.send(jsonString);
    }
  </script>
</body>
</html>
)=====";
