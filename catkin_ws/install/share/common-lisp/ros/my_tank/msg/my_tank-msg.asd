
(cl:in-package :asdf)

(defsystem "my_tank-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "odoms" :depends-on ("_package_odoms"))
    (:file "_package_odoms" :depends-on ("_package"))
  ))