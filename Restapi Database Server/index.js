
const express = require('express');
const mongoose = require('mongoose');
const mongoString = "mongodb+srv://maryamahass12:admin@cluster0.vzyejai.mongodb.net/?retryWrites=true&w=majority";
const routes = require('./routes/router');
const ProductModel = require("./models/datamodel");

mongoose.connect( mongoString );
const database = mongoose.connection;

database.on('error', (error) => {
    console.log(error)
})

database.once('connected', () => {
    console.log('Database Connected');
})
const app = express();
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use('/api',routes)

app.listen(2002, () => {
  console.log(`Server Started at ${2002}`)
})