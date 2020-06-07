const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;
app.use(bodyParser.urlencoded({ extended: false }))
app.set('view engine', 'ejs');
app.use(express.static(__dirname + '/public'));
app.get('/', (req, res, next) => {
    res.render('main');
});
app.listen(port, () => {
    console.log("Server is running at port:", port);
})