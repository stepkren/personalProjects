package cz.cvut.fit.tjv.reservationdatabase.controller;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.application.CustomerServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.application.RestaurantServiceInterface;
import cz.cvut.fit.tjv.reservationdatabase.controller.converter.DTOConverter;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CuisineDTO;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CustomerDTO;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.RestaurantDTO;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/rest/api/customer")
public class CustomerController {

    private final CustomerServiceInterface customerService;

    private final CuisineServiceInterface cuisineService;

    private final RestaurantServiceInterface restaurantService;

    private final DTOConverter<CustomerDTO, Customer> customerDTOConverter;

    private final DTOConverter<CuisineDTO, Cuisine> cuisineDTOConverter;

    private final DTOConverter<RestaurantDTO, Restaurant> restaurantDTOConverter;

    private CustomerController (CustomerServiceInterface customerService, CuisineServiceInterface cuisineService, RestaurantServiceInterface restaurantService,
                                DTOConverter<CuisineDTO, Cuisine> cuisineDTOConverter,
                                DTOConverter<RestaurantDTO, Restaurant> restaurantDTOConverter,
                                DTOConverter<CustomerDTO, Customer> customerDTOConverter) {
        this.customerService = customerService;
        this.cuisineService = cuisineService;
        this.restaurantService = restaurantService;
        this.customerDTOConverter = customerDTOConverter;
        this.cuisineDTOConverter = cuisineDTOConverter;
        this.restaurantDTOConverter = restaurantDTOConverter;
    }

    @Operation(summary = "Gets all customers")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "List of customers successfully retrieved")
    })
    @GetMapping
    public List<CustomerDTO> getCustomers() {
        return customerService.getCustomers().stream().map(customerDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Gets customer specified by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved customer"),
            @ApiResponse(responseCode = "404", description = "Customer not found"),
    })
    @GetMapping(path = "{id}")
    public CustomerDTO getCustomer(@PathVariable("id") Long id) {
        return customerDTOConverter.toDTO(customerService.getCustomerById(id));
    }

    @Operation(summary = "Gets restaurants visited by customer specified by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "List of restaurants successfully retrieves"),
            @ApiResponse(responseCode = "404", description = "Customer not found"),
    })
    @GetMapping(path = "{id}/visited")
    public List<RestaurantDTO> getCustomersVisited (@PathVariable("id") Long id) {
        return customerService.getCustomerById(id).getVisited().stream().map(restaurantDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Adds visited restaurant to customer")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully added visited restaurant to customer"),
            @ApiResponse(responseCode = "400", description = "Restaurant isn't yet open"),
            @ApiResponse(responseCode = "404", description = "Customer or restaurant not found")
    })
    @PostMapping(path = "{id}/visited")
    public List<RestaurantDTO> addVisited (@PathVariable("id") Long customerId, @RequestBody Long restaurantId) {
        customerService.addRestaurantToCustomer(restaurantId, customerId);
        return customerService.getCustomerById(customerId).getVisited().stream().map(restaurantDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Removes visited restaurant from customer")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully added visited restaurant to customer"),
            @ApiResponse(responseCode = "400", description = "Customer didn't visit restaurant"),
            @ApiResponse(responseCode = "404", description = "Customer or restaurant not found")
    })
    @DeleteMapping(path = "{customerId}/visited/{restaurantId}")
    public List<RestaurantDTO> removeVisited (@PathVariable("customerId") Long customerId, @PathVariable("restaurantId") Long restaurantId) {
        customerService.removeRestaurantFromCustomer(restaurantId, customerId);
        return customerService.getCustomerById(customerId).getVisited().stream().map(restaurantDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Gets all customers that visited a restaurant cooking a specified cuisine by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved list of customers"),
            @ApiResponse(responseCode = "400", description = "Invalid cuisine id given")
    })
    @GetMapping(path = "specific")
    public List<CustomerDTO> findCustomerThatVisitedRestaurantCookingCuisine (@RequestParam("cu") Long cuisineId) {
        Cuisine cuisine = cuisineService.getCuisineById(cuisineId);
        return customerService.findCustomerThatVisitedRestaurantCookingCuisine(cuisine).stream().map(customerDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Creates a new customer")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully created new customer"),
            @ApiResponse(responseCode = "400", description = "Invalid phone number or email given")
    })
    @PostMapping
    public CustomerDTO createCustomer(@RequestBody CustomerDTO c) {
        return customerDTOConverter.toDTO(customerService.createCustomer(customerDTOConverter.toEntity(c)));
    }

    @Operation(summary = "Updates existing customer")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully updated customer"),
            @ApiResponse(responseCode = "400", description = "Invalid customer given")
    })
    @PutMapping(path = "{id}")
    public CustomerDTO updateCustomer(@PathVariable Long id, @RequestBody CustomerDTO c) {
        Customer customerEntity = customerDTOConverter.toEntity(c);
        customerEntity.setCustomerId(id);
        return customerDTOConverter.toDTO(customerService.updateCustomer(customerEntity));
    }

    @Operation(summary = "Deletes existing customer")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully deleted customer"),
            @ApiResponse(responseCode = "404", description = "Customer doesn't exist")
    })
    @DeleteMapping(path = "{id}")
    public void deleteCustomer(@PathVariable Long id) {
        customerService.deleteCustomer(id);
    }
}
