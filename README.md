# Split_keyboard

自作分割キーボード(2号機)のデータ一式。

- `3d/` — ケースの3Dプリント用STL(上面プレート・側面パーツ、L手/R手それぞれ)
- `firmware/kb2_l/`, `firmware/kb2_r/` — vial-qmkのキーボードソース(ビルド前)
- `firmware/uf2/` — コンパイル済み`.uf2`の置き場所(各自の`qmk compile`実行結果をここに入れる)

## ビルド方法

```
qmk compile -kb kb2_l -km default
qmk compile -kb kb2_r -km default
```

生成された`.uf2`をRP2040にドラッグ&ドロップで書き込む(BOOTSELモードで接続)。
