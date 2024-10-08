const mongoose = require("mongoose");
mongoose.set('strictQuery', true);  

const DataSchema = mongoose.Schema({
    xValue: {type: Number },
    yValue: {type: Number },
    zValue: {type: Number },
});

module.exports = mongoose.model("products", DataSchema);
