; Auto-generated. Do not edit!


(cl:in-package my_tank-msg)


;//! \htmlinclude odoms.msg.html

(cl:defclass <odoms> (roslisp-msg-protocol:ros-message)
  ((linear
    :reader linear
    :initarg :linear
    :type cl:float
    :initform 0.0)
   (angular
    :reader angular
    :initarg :angular
    :type cl:float
    :initform 0.0))
)

(cl:defclass odoms (<odoms>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <odoms>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'odoms)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_tank-msg:<odoms> is deprecated: use my_tank-msg:odoms instead.")))

(cl:ensure-generic-function 'linear-val :lambda-list '(m))
(cl:defmethod linear-val ((m <odoms>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_tank-msg:linear-val is deprecated.  Use my_tank-msg:linear instead.")
  (linear m))

(cl:ensure-generic-function 'angular-val :lambda-list '(m))
(cl:defmethod angular-val ((m <odoms>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_tank-msg:angular-val is deprecated.  Use my_tank-msg:angular instead.")
  (angular m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <odoms>) ostream)
  "Serializes a message object of type '<odoms>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'linear))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angular))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <odoms>) istream)
  "Deserializes a message object of type '<odoms>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linear) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angular) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<odoms>)))
  "Returns string type for a message object of type '<odoms>"
  "my_tank/odoms")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'odoms)))
  "Returns string type for a message object of type 'odoms"
  "my_tank/odoms")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<odoms>)))
  "Returns md5sum for a message object of type '<odoms>"
  "9d5c2dcd348ac8f76ce2a4307bd63a13")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'odoms)))
  "Returns md5sum for a message object of type 'odoms"
  "9d5c2dcd348ac8f76ce2a4307bd63a13")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<odoms>)))
  "Returns full string definition for message of type '<odoms>"
  (cl:format cl:nil "float32 linear~%float32 angular~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'odoms)))
  "Returns full string definition for message of type 'odoms"
  (cl:format cl:nil "float32 linear~%float32 angular~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <odoms>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <odoms>))
  "Converts a ROS message object to a list"
  (cl:list 'odoms
    (cl:cons ':linear (linear msg))
    (cl:cons ':angular (angular msg))
))
