/^# Packages using this file: / {
  s/# Packages using this file://
  ta
  :a
  s/ nc6 / nc6 /
  tb
  s/ $/ nc6 /
  :b
  s/^/# Packages using this file:/
}
