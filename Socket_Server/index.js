var PORT = 3060;

var http = require("http");
var socketio = require("socket.io");
var app = http.createServer();
var io = socketio(app);

app.listen(PORT, () => {
  console.log("Socket Server is running ar port:" + PORT);
});

io.on("connection", (socket) => {
  //Connect socket successfull
  console.log("Connected");
  //Listen to event set speed from web
  socket.on("setSpeed", (data) => {
    console.log("Speed is", data.speed);
    //Emit event to hardware
    socket.emit("setSpeedHardware", { data2: data.speed });
  });
  socket.on("resSpeed", (data) => {
    socket.emit("displaySpeed", { resSpeed: data.speed });
  });
  socket.emit('displaySpeed',{resSpeed: 100})
});
