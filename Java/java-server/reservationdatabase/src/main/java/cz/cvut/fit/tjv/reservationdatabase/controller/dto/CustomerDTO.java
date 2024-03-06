package cz.cvut.fit.tjv.reservationdatabase.controller.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.List;

@Getter
@AllArgsConstructor
public class CustomerDTO {

    private final Long customerId;

    private final String name;

    private final String phoneNumber;

    private final String email;

    private final List<Long> restaurantIds;
}
