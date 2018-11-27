# STL 注意事项

---

## Vector 容器
1.假设vector中存储的元素是一个结构体，那么当不断往vector中push_back元素的时候，新加的元素都是放在栈空间里，使用结束后调用clear()函数这些空间也不会释放，想要释放这些空间，有如下办法：
(1)定义一个作用域，超过作用域vector中的元素就会立即释放。
(2)使用new声明vector，这样整个vector放在堆上，不用的时候可以使用delete立即释放。

---

## List 容器

---

## sort 算法

stable_sort

---

