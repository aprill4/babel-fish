define void @putint(i32 ) {
putint1:
  ret void
}
define void @putch(i32 ) {
putch3:
  ret void
}
define i32 @getint() {
getint4:
  ret i32 0
}
define i32 @getch() {
getch6:
  ret i32 0
}
define i32 @main() {
main8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  store i32 5, i32* %v9
  store i32 5, i32* %v11
  store i32 1, i32* %v13
  %v24 = sub nsw i32 0, 2
  store i32 %v24, i32* %v15
  store i32 2, i32* %v17
  %v31 = load i32, i32* %v15
  %v33 = mul i32 %v31, 1
  %v35 = sdiv i32 %v33, 2
  %bool_37 = icmp slt i32 %v35, 0
  %bool_39 = icmp ne i1 %bool_37, zeroinitializer
  br i1 %bool_39, label %l29, label %r30
if_true_entry26:
  %v58 = load i32, i32* %v17
  call void @putint(i32 %v58)
  br label %next_entry28
next_entry28:
  %v65 = load i32, i32* %v15
  %v67 = srem i32 %v65, 2
  %v69 = add nsw i32 %v67, 67
  %bool_71 = icmp slt i32 %v69, 0
  %bool_73 = icmp ne i1 %bool_71, zeroinitializer
  br i1 %bool_73, label %l63, label %r64
l29:
  br label %if_true_entry26
r30:
  %v42 = load i32, i32* %v9
  %v43 = load i32, i32* %v11
  %v44 = sub nsw i32 %v42, %v43
  %bool_46 = icmp ne i32 %v44, 0
  %bool_48 = icmp ne i1 %bool_46, zeroinitializer
  br i1 %bool_48, label %l40, label %r41
l40:
  %v49 = load i32, i32* %v13
  %v51 = add nsw i32 %v49, 3
  %v53 = srem i32 %v51, 2
  %bool_55 = icmp ne i32 %v53, 0
  %bool_57 = icmp ne i1 %bool_55, zeroinitializer
  br i1 %bool_57, label %if_true_entry26, label %r41
r41:
  br label %next_entry28
if_true_entry60:
  store i32 4, i32* %v17
  %v93 = load i32, i32* %v17
  call void @putint(i32 %v93)
  br label %next_entry62
next_entry62:
  ret i32 0
l63:
  br label %if_true_entry60
r64:
  %v76 = load i32, i32* %v9
  %v77 = load i32, i32* %v11
  %v78 = sub nsw i32 %v76, %v77
  %bool_80 = icmp ne i32 %v78, 0
  %bool_82 = icmp ne i1 %bool_80, zeroinitializer
  br i1 %bool_82, label %l74, label %r75
l74:
  %v83 = load i32, i32* %v13
  %v85 = add nsw i32 %v83, 2
  %v87 = srem i32 %v85, 2
  %bool_89 = icmp ne i32 %v87, 0
  %bool_91 = icmp ne i1 %bool_89, zeroinitializer
  br i1 %bool_91, label %if_true_entry60, label %r75
r75:
  br label %next_entry62
}

