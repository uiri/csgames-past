from aiclient.AIDefault import AIDefault


class MyAI(AIDefault):
    '''
    Class for you to add your intelligence to the AI,
    you can use the super() methods to access the default AI
    or create your own using the code in AiDefault
    '''
    def tick(self):
        # Only essential method
        isinstance(self, AIDefault)
        super().tick()  # Replace this line with your AI
