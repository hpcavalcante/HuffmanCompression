all: 
	@make --no-print-directory -C ./encoder all
	@make --no-print-directory -C ./decoder all
	@mkdir -p ./bin
	@cp ./encoder/encoder ./bin/ 
	@cp ./decoder/decoder ./bin/ 

clean: 
	@make --no-print-directory -C ./encoder clean
	@make --no-print-directory -C ./decoder clean
	rm -rf ./bin/

fclean: clean
	@make --no-print-directory -C ./encoder fclean
	@make --no-print-directory -C ./decoder fclean
	rm -rf ./bin/

re: fclean all

.PHONY: all  clean fclean re