; 2. Uživatelské funkce a prostředí
#|!|#
(defun > (a b)
  "Tests the inequality x > y."
  (< b a))

#|!|#
(defun <= (a b)
  "Tests the inequality x <= y."
  (not (> a b)))

#|!|#
(defun rem (a b)
  "Returns remainer after division"
  (let ((div (div a b)))
    (- a (* div b))))

#|!|#
(defun power2 (a)
"Returns second power of A"
   (* a a))

#|!|#
(defun minusp (a)
  "Returns True if A is negative, otherwise returns False"
  (< a 0))

#|!|#
(defun abs (a)
  "Returns the absolute value of A"
  (if (plusp a)
      a
    (- a)))

#|!|#
(defun min (a b)
  "Returns the smaller of a or b"
  (if (< a b)
      a
    b))

#|!|#
(defun max (a b)
  "Returns the bigger of a or b"
  (if (> a b)
      a
    b))

; 3. Rekurzivní funkce

#|!|#
(defun gcd (a b)
  "Returns greatest common divisor of a and b"
  (if (= b 0)
      a
    (gcd b (% a b))))



; 4. Rekurzivní výpočetní proces

#|!|#
(defun primep (n)
  "Returns True if n is a prime"
  (labels ((divisible-p (n i max)
             (or (> i max)
                 (= (rem n i) 0)
                 (divisible-p n (+ i 1) max))))
    (and (> n 1)
         (not (divisible-p n 2 (floor (sqrt n)))))))

#|!|#
(defun dividesp (a n)
  "Returns True if a divides n without a remainder"
  (zerop (rem n a)))

#|!|#
(defun fib-tail (n)
  "Returns the n-th Fibonacci number using tail recursion."
  (labels ((fib-helper (a b n)
             (if (<= n 0)
                 a
                 (fib-helper b (+ a b) (- n 1)))))
    (fib-helper 0 1 n)))

; 5. Páry a seznamy

#|!|#
(defun position (element list)
  "Returns the position of the element in the list"
  (or (and (not (null list))
           (eql element (car list)) 0)
      (and (not (null list))
           (position element (cdr list))
           (+ 1 (position element (cdr list))))))

#|!|#
(defun mismatch (list1 list2)
  "Returns the position at which the lists differ"
  (labels ((mismatch-iter (list1 list2 index)
             (cond
              ((and (null list1) (null list2)) nil)
              ((or (null list1) (null list2)) index)
              ((not (eql (car list1) (car list2))) index)
              (t (mismatch-iter (cdr list1) (cdr list2) (+ index 1))))))
    (mismatch-iter list1 list2 0)))

#|!|#
(defun last (list n)
  "Returns the last n elements from the right"
  (labels ((last-iter (list remaining)
             (cond  ((< remaining 0) (abs remaining))
                    ((= remaining 0) list)
                    (t (last-iter (cdr list) (- remaining 1))) ))   )
    (last-iter list (- (length list) n ))))

; 6. Vstup a výstup