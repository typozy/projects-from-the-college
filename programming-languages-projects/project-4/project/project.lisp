(defun parser (listtoparse)
	(labels 
		((do-write (stream listtoparse)
			(cond ((null listtoparse) (format stream "~%"))
				(t (format stream "\(\"~D\" \"~D\"\)~%" (caar listtoparse)(cadar listtoparse)) 
				(do-write stream (cdr listtoparse)))
			)
		))
		(with-open-file (stream "161044083.tree"
							:direction :output
							:if-exists :append
							:if-does-not-exist :create)
			(format stream "; DIRECTIVE: print~%")
			(do-write stream listtoparse)
		)
	)
)