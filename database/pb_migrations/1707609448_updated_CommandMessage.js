/// <reference path="../pb_data/types.d.ts" />
migrate((db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("s3u9kc1izqjaeds")

  // remove
  collection.schema.removeField("rs9i54mh")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "1qgrrjnp",
    "name": "target",
    "type": "text",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "min": null,
      "max": null,
      "pattern": ""
    }
  }))

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "nzietjqt",
    "name": "command",
    "type": "text",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "min": null,
      "max": null,
      "pattern": ""
    }
  }))

  return dao.saveCollection(collection)
}, (db) => {
  const dao = new Dao(db)
  const collection = dao.findCollectionByNameOrId("s3u9kc1izqjaeds")

  // add
  collection.schema.addField(new SchemaField({
    "system": false,
    "id": "rs9i54mh",
    "name": "command_enum",
    "type": "number",
    "required": false,
    "presentable": false,
    "unique": false,
    "options": {
      "min": null,
      "max": null,
      "noDecimal": false
    }
  }))

  // remove
  collection.schema.removeField("1qgrrjnp")

  // remove
  collection.schema.removeField("nzietjqt")

  return dao.saveCollection(collection)
})
