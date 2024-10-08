const express = require("express");
const router = express.Router();
const { Model, model } = require("mongoose");
const datamodel = require("../models/datamodel");

router.post("/", async function (req, res, next) {
  console.log("req.body: ", req.body);
  try {
    const productInstance = new datamodel({
      x: req.body.xValue,
      y: req.body.yValue,
    });
    const saveResult = await datamodel.save();
    res.status(201).json(saveResult);
  } catch (error) {
    res.status(500).json(error);
  }
});

router.get("/", async function (req, res) {
  const products = await datamodel.find().sort({ name: "asc" });
  res.status(200).json();
});

router.get("/:id", async function (req, res) {
  try {
    const product = await datamodel.findOne({ _id: req.params.id });
    res.status(200).json(product);
  } catch (error) {
    res.status(404).json(error);
  }
});

router.get("/latest/:max", async function (req, res) {
  try {
    const products = await datamodel.find()
      .limit(req.params.max)
      .sort({ modifiedDate: "desc" });
    res.status(200).json(products);
  } catch (error) {
    res.status(404).json(error);
  }
});

router.put("/:id", async function (req, res) {
  console.log("req.body: ", req.body);
  try {
    const product = await datamodel.findById(req.params.id);
    try {
      // if we got a result, move on
      product.name = req.query.name;
      product.categories = req.query.categories;
      const result = await datamodel.save();
      res.status(200).json(result);
    } catch (error) {
      res.status(400).json("{}");
    }
  } catch (error) {
    res
      .status(404)
      .json("{'error':'No object with ID " + req.params.id + " in DB}");
  }
});

router.delete("/:id", async function (req, res) {
  try {
    const product = await datamodel.deleteOne({ _id: req.params.id });
    res.status(200).json(product);
  } catch (error) {
    return res.status(404).json("{}");
  }
});

module.exports = router;
