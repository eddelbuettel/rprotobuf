; Emacs customization settings to apply to every file in this directory.
; See http://www.emacswiki.org/emacs/DirectoryVariables
;
; Note some of the files include '{{{' and '}}}' annotations to be used
; with Folding Mode: http://www.emacswiki.org/emacs/FoldingMode
((nil . ((indent-tabs-mode . nil)
         (tab-width . 4)
         (show-trailing-whitespace . t)))
 (c-mode . ((c-indent-level . 4)
            (c-basic-offset . 4)
            (show-trailing-whitespace . t)))
 (c++-mode . ((c-indent-level . 4)
              (c-basic-offset . 4)
              (show-trailing-whitespace . t))))
