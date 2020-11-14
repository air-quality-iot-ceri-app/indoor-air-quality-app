
//const browser = require('socket.io')();


var  express = require('express')


const nodeRed = express()
const browser = express()

// ajout de socket.io
const server = require('http').Server(browser)
const io = require('socket.io')(server, {origins:'localhost:* localhost:* localhost:* ws://localhost:3001'})

//const io = IO.of('/ws', {transports: ['websocket']});


//

nodeRed.use(express.json())
browser.use(express.json())

browser.use(express.static('public'));




nodeRed.post('/', (req, res) => {
  console.log(req.body) // <-- this will access the body of the post
  res.json("okay!")
  io.emit("new", req.data)
})
nodeRed.listen(3000);
//console.log("Server Node Red is running !!");


console.log("Server Node Red is running !!");


//-------------------------------------- Browser Part --------------------------

// établissement de la connexion
io.on('connection', (socket) =>{
    console.log(`Connecté au client ${socket.id}`)
})


browser.get('/', (req, res) => {
    console.log(req.body) // <-- this will access the body of the post
    res.sendFile("index.html")
    //browser.emit("new", req.data)
    console.log("Envoie au browser");
  })
server.listen(3001);
//io.listen(3001)
//io.listen(3002)
console.log("Server Node Red is running !!");
