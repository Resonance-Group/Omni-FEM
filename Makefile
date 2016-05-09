.PHONY: clean All

All:
	@echo "----------Building project:[ Omni-FEM - Debug ]----------"
	@"$(MAKE)" -f  "Omni-FEM.mk"
clean:
	@echo "----------Cleaning project:[ Omni-FEM - Debug ]----------"
	@"$(MAKE)" -f  "Omni-FEM.mk" clean
