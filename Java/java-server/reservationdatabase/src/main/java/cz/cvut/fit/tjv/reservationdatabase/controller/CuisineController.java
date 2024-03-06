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
import org.springframework.jmx.export.annotation.ManagedOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/rest/api/cuisine")
public class CuisineController {
    private final CustomerServiceInterface customerService;

    private final CuisineServiceInterface cuisineService;

    private final RestaurantServiceInterface restaurantService;

    private final DTOConverter<CustomerDTO, Customer> customerDTOConverter;

    private final DTOConverter<CuisineDTO, Cuisine> cuisineDTOConverter;

    private final DTOConverter<RestaurantDTO, Restaurant> restaurantDTOConverter;

    private CuisineController (CustomerServiceInterface customerService, CuisineServiceInterface cuisineService, RestaurantServiceInterface restaurantService,
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

    @Operation(summary = "Gets all cuisines")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved the list of cuisines"),
    })
    @GetMapping
    public List<CuisineDTO> getCuisines() {
        return cuisineService.getCuisines().stream().map(cuisineDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Gets cuisine specified by id")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Cuisine successfully retrieved"),
            @ApiResponse(responseCode = "404", description = "Cuisine not found")
    })
    @GetMapping(path = "{id}")
    public CuisineDTO getCuisine(@PathVariable("id") Long id) {
        return cuisineDTOConverter.toDTO(cuisineService.getCuisineById(id));
    }

    @Operation(summary = "Gets restaurants where specified cuisine is cooked")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Successfully retrieved list of restaurants"),
            @ApiResponse(responseCode = "404", description = "Cuisine not found")
    })
    @GetMapping(path = "{id}/cookedAt")
    public List<RestaurantDTO> getRestaurantsWhereIsCooked (@PathVariable("id") Long id) {
        return cuisineService.getCuisineById(id).getIsCookedAt().stream().map(restaurantDTOConverter::toDTO).toList();
    }

    @Operation(summary = "Creates a new cuisine")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Cuisine created successfully"),
            @ApiResponse(responseCode = "400", description = "Invalid cuisine given"),
    })
    @PostMapping
    public CuisineDTO createCuisine (@RequestBody CuisineDTO cu) {
        return cuisineDTOConverter.toDTO(cuisineService.createCuisine(cuisineDTOConverter.toEntity(cu)));
    }

    @Operation(summary = "Updated existing cuisine")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Cuisine updated successfully"),
            @ApiResponse(responseCode = "400", description = "Invalid cuisine given"),
    })
    @PutMapping(path = "{id}")
    public CuisineDTO updateCuisine (@PathVariable Long id, @RequestBody CuisineDTO cu) {
        Cuisine cuisineEntity = cuisineDTOConverter.toEntity(cu);
        cuisineEntity.setCuisineId(id);
        return cuisineDTOConverter.toDTO(cuisineService.updateCuisine(cuisineEntity));
    }

    @Operation(summary = "Delete existing cuisine")
    @ApiResponses(value = {
            @ApiResponse(responseCode = "200", description = "Cuisine deleted successfully"),
            @ApiResponse(responseCode = "404", description = "Cuisine not found"),
    })
    @DeleteMapping(path = "{id}")
    public void deleteCuisine (@PathVariable Long id) {
        cuisineService.deleteCuisine(id);
    }
}
