#|
Soubor obsahuje většinu funkcí z přednášek a cvičení z kurzu PP1, které
budeme potřebovat v PP2.
Implementace některých z nich je mírně odlišná, hlavně ze dvou důvodů:

- kde to lze, používá se koncová rekurze
- nepoužívají se operátory let, let* a cond, které v jazyce PP2 nejsou

Většina funkcí vyššího řádu zatím chybí, napíšeme si je ponovu v první
přednášce a cvičení.
|#

#|

LOGIKA

|#

(defun not (x)
  "Logical negation of x"
  (eql x nil))

#|

ČÍSLA

|#

(defun > (a b)
  "Tests the inequality x > y."
  (< b a))

(defun >= (a b)
  "Tests the inequality x >= y."
  (not (< a b)))

(defun <= (a b)
  "Tests the inequality a <= b"
  (not (> a b)))

(defun 1+ (x)
  (+ x 1))

(defun 1- (x)
  (- x 1))

(defun plusp (a)
  "Returns True if A is positive, otherwise returns False."
  (> a 0))

(defun zerop (a)
  "Returns True if A is equal to 0, otherwise returns False."
  (= a 0))

(defun minusp (a)
  "Returns the logical value of a < 0."
  (< a 0))

(defun abs (a)
  "Returns the absolute value of a."
  (if (minusp a)
      (- a)
    a))

(defun div (a b)
  "Computes the integer quotient a / b.
Result is the greatest integer c such that c <= a/b."
  (floor (/ a b)))

(defun rem (a b)
  "Computes the remainder of the integer division a / b."
 (- a (* (div a b) b)))

(defun evenp (n)
  (= 0 (rem n 2)))

(defun oddp (n)
  (= 1 (rem n 2)))

(defun gcd (a b)
  (if (= b 0)
      a
    (gcd b (rem a b))))

(defun min (number &rest numbers)
  "Returns the smallest of given numbers."
  (foldl (lambda (a b)
           (if (<= a b) a b))
         numbers
         number))

(defun max (number &rest numbers)
  "Returns the greatest of given numbers."
  (foldl (lambda (a b)
           (if (>= a b) a b))
         numbers
         number))

#|

JEDNODUCHÉ FUNKCE

|#

(defun identity (x)
  x)


#|

PÁRY A SEZNAMY

|#

(defun null (elem)
  (eql elem nil))

(defun atom (elem)
  (not (consp elem)))

(defun caar (x)
  (car (car x)))

(defun cadr (x)
  (car (cdr x)))

(defun cdar (x)
  (cdr (car x)))

(defun cddr (x)
  (cdr (cdr x)))

(defun caaar (x)
  (car (car (car x))))

(defun caadr (x)
  (car (car (cdr x))))

(defun cadar (x)
  (car (cdr (car x))))

(defun caddr (x)
  (car (cdr (cdr x))))

(defun cdaar (x)
  (cdr (car (car x))))

(defun cdadr (x)
  (cdr (car (cdr x))))

(defun cddar (x)
  (cdr (cdr (car x))))

(defun cdddr (x)
  (cdr (cdr (cdr x))))

(defun caaaar (x)
  (car (car (car (car x)))))

(defun caaadr (x)
  (car (car (car (cdr x)))))

(defun caadar (x)
  (car (car (cdr (car x)))))

(defun caaddr (x)
  (car (car (cdr (cdr x)))))

(defun cadaar (x)
  (car (cdr (car (car x)))))

(defun cadadr (x)
  (car (cdr (car (cdr x)))))

(defun caddar (x)
  (car (cdr (cdr (car x)))))

(defun cadddr (x)
  (car (cdr (cdr (cdr x)))))

(defun cdaaar (x)
  (cdr (car (car (car x)))))

(defun cdaadr (x)
  (cdr (car (car (cdr x)))))

(defun cdadar (x)
  (cdr (car (cdr (car x)))))

(defun cdaddr (x)
  (cdr (car (cdr (cdr x)))))

(defun cddaar (x)
  (cdr (cdr (car (car x)))))

(defun cddadr (x)
  (cdr (cdr (car (cdr x)))))

(defun cdddar (x)
  (cdr (cdr (cdr (car x)))))

(defun cddddr (x)
  (cdr (cdr (cdr (cdr x)))))

(defun length (list)
  (labels ((len (lst ir)
             (if (null lst)
                 ir
               (len (cdr lst) (1+ ir)))))
    (len list 0)))

(defun nthcdr (n list)
  (if (= n 0)
      list
    (nthcdr (- n 1) (cdr list))))

(defun nth (n list)
  (car (nthcdr n list)))

(defun first (list)
  (nth 0 list))

(defun second (list)
  (nth 1 list))

(defun third (list)
  (nth 2 list))

(defun fourth (list)
  (nth 3 list))

(defun fifth (list)
  (nth 4 list))

(defun sixth (list)
  (nth 5 list))

(defun seventh (list)
  (nth 6 list))

(defun eighth (list)
  (nth 7 list))

(defun ninth (list)
  (nth 8 list))

(defun tenth (list)
  (nth 9 list))

(defun last (list n)
  (labels ((%last (diff)
             (if (plusp diff)
                 (nthcdr diff list)
               nil)))
    (%last (- (length list) n))))

(defun copy-list (list)
  (if (null list)
      nil
    (cons (car list)
          (copy-list (cdr list)))))

(defun list (&rest elements)
  (copy-list elements))

(defun revappend (list1 list2)
  (if (null list1)
      list2
    (revappend (cdr list1)
               (cons (car list1) list2))))

(defun reverse (list)
  (revappend list nil))

(defun tailp (list1 list2)
  (if (null list1)
      t
    (if (null list2)
        nil
      (if (eql list1 list2)
          t
        (tailp list1 (cdr list2))))))

(defun ldiff (list1 list2)
  (if (null list2)
      list1
    (if (null list1)
        nil
      (if (eql list1 list2)
          nil
        (cons (car list1)
              (ldiff (cdr list1) list2))))))

(defun every (predicate list)
  (if (null list)
      t
    (if (funcall predicate (car list))
        (every predicate (cdr list))
      nil)))

(defun some (predicate list)
  (if (null list)
      nil
    (if (funcall predicate (car list))
        t
      (some predicate (cdr list)))))

(defun mapcar (function list1 &rest lists)
  "Every argument starting from the second one must be a list of the same length.
The first argument must be a function accepting the same number of arguments as is
the count of supplied lists. The result is a list of the same length as the lengths
of the supplied lists. The first element of the result is the result of application
of FUNCTION to first elements of the list, the second one to second, etc."
  (labels ((mapcar-1 (f list)
             (if (null list)
                 '()
               (cons (funcall f (car list))
                     (mapcar-1 f (cdr list))))))
    (if (null list1)
        '()
      (cons (apply function (mapcar-1 #'car (cons list1 lists)))
            (apply #'mapcar function (cdr list1) (mapcar-1 #'cdr lists))))))

(defun mapcan (function list1 &rest lists)
  (apply #'list (apply #'mapcar function list1 lists)))

(defun foldr (fun list init)
  "Applies FUN to the last element of LIST and INIT, then to the second last
element and the result of the previous application, etc. Returns the result of the
last application of FUN (to the first element and the result of the previous
application). If LIST is empty, returns INIT."
  (if (null list)
      init
    (funcall fun
             (car list)
             (foldr fun (cdr list) init))))

(defun foldl (fun list init)
  "Applies FUN to INIT and the first element of LIST, then to the second
element and the result of the previous application, etc. Returns the result of the
last application of FUN. If LIST is empty, returns INIT."
  (labels ((%foldl (l res)
             (if (null l)
                 res
               (%foldl (cdr l) (funcall fun res (car l))))))
    (%foldl list init)))

(defun append (&rest lists)
  "Returns a list created by joining given lists."
  (labels ((app-2 (l1 l2)
             (foldr #'cons l1 l2)))
    (foldr #'app-2 lists '())))


#|

FUNKCE VYŠŠÍHO ŘÁDU

|#

(defun constantly (c)
  (lambda (n) c))

(defun complement (predicate)
  (lambda (&rest args)
    (not (apply predicate args))))



