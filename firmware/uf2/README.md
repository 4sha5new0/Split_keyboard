# uf2 files

The compiled `.uf2` firmware files are not included here — they were only
ever produced on the local machine that ran `qmk compile` (this repo
only has the pre-build source under `firmware/kb2_l` and `firmware/kb2_r`).

Drop your own build output here:

- `kb2_l_default.uf2`
- `kb2_r_default.uf2`

Rebuild anytime with:

```
qmk compile -kb kb2_l -km default
qmk compile -kb kb2_r -km default
```
