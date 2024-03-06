package cz.cvut.fit.tjv.reservationdatabase.controller;

import jakarta.persistence.EntityNotFoundException;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.context.request.WebRequest;
import org.springframework.web.servlet.mvc.method.annotation.ResponseEntityExceptionHandler;

@ControllerAdvice
public class RestExceptionHandler extends ResponseEntityExceptionHandler {

    @ExceptionHandler(value = {IllegalArgumentException.class})
    protected ResponseEntity<Object> handleIllegalArgument (RuntimeException runtimeException, WebRequest webRequest) {
        String body = "Given argument is illegal!";
        return handleExceptionInternal(runtimeException, body, new HttpHeaders(), HttpStatus.BAD_REQUEST, webRequest);
    }

    @ExceptionHandler(value = {EntityNotFoundException.class})
    protected ResponseEntity<Object> handleEntityDoesntExist (RuntimeException runtimeException, WebRequest webRequest) {
        String body = "Given entity doesn't exist!";
        return handleExceptionInternal(runtimeException, body, new HttpHeaders(), HttpStatus.NOT_FOUND, webRequest);
    }
}
